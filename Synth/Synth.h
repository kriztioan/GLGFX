/**
 *  @file   Synth.h
 *  @brief  Music Synthesizer in CBGLGFX
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef CBGLGFX_SYNTH_H
#define CBGLGFX_SYNTH_H

#include "../Audio.h"
#include "../GLGFX.h"
#include "../Widgets.h"

#include <cmath>
extern "C" {
#include <fftw3.h>
#include <unistd.h>
}
#include <algorithm>
#include <climits>

bool wave_type_callback(cb::WidgetButton *button, void *userdata);
bool window_type_callback(cb::WidgetButton *button, void *userdata);
bool quit_callback(cb::WidgetButton *button, void *userdata);

typedef struct {
  float *ones;
  float *hanning;
  float *hamming;
  float *window;
} Windows;
class Synth : public cb::Audio, public cb::GLGFX {

public:
  enum WAVE_T { WAVE_SINE, WAVE_SQUARE, WAVE_TRIANGLE, WAVE_SAW, WAVE_NOISE };

  enum WINDOW_T { WINDOW_NONE, WINDOW_HANNING, WINDOW_HAMMING };

  Synth() {

    sTitle = "Synthesizer";
    bShowFPS = false;
    bVSync = true;

    SetAudioSamplerate(44100);
    SetAudioStereo(1);
    SetBitsPerChannel(sizeof(short) * 8);

    sample_max = samplerate / 2;
    sample_min = sample_max / sample_size;

    SetCallback(callback);

    sample = fftwf_alloc_real(sample_size);

    windows.ones = fftwf_alloc_real(sample_size);
    std::fill_n(windows.ones, sample_size, 1.0f);

    windows.hanning = fftwf_alloc_real(sample_size);
    for (int i = 0; i < sample_size; i++)
      windows.hanning[i] =
          0.5f - 0.5f * std::cos(2.0f * M_PI * static_cast<float>(i) /
                                 static_cast<float>(sample_size - 1));
    windows.hamming = fftwf_alloc_real(sample_size);
    for (int i = 0; i < sample_size; i++)
      windows.hamming[i] =
          0.54f - 0.46f * std::cos(2.0f * M_PI * static_cast<float>(i) /
                                   static_cast<float>(sample_size - 1));

    windows.window = windows.ones;

    fft = fftwf_alloc_complex(1 + sample_size / 2);

    bool bHasWisdom = access(plan_filename, F_OK | R_OK) == 0;
    if (bHasWisdom) {
      fftwf_import_wisdom_from_filename(plan_filename);
    }
    plan = fftwf_plan_dft_r2c_1d(sample_size, sample, fft, FFTW_EXHAUSTIVE);
    if (!bHasWisdom) {
      fftwf_export_wisdom_to_filename(plan_filename);
    }
  }

  void OnUserDestroy() final {
    fftwf_free(sample);
    fftwf_free(windows.ones);
    fftwf_free(windows.hanning);
    fftwf_free(windows.hamming);
    fftw_free(fft);
    fftwf_destroy_plan(plan);
  }

  bool OnUserCreate() final {

    cb::WidgetRadioGroup radio_wave_type, radio_window_type;

    cb::WidgetButton button;
    button.xpos = 0;
    button.width = 37;
    button.color = FG_RED;
    button.border = FG_BLACK;
    button.userdata = (void *)&wave_type;
    button.callback = wave_type_callback;
    for (const auto &text :
         std::array<std::string, 5>({"SIN", "SQ", "TRI", "SAW", "NOI"})) {

      button.text = text;

      radio_wave_type.add(button);
      button.xpos += button.width + 1;
    }
    radio_wave_type.select(WAVE_SINE);

    button.color = FG_GREEN;
    button.border = FG_BLACK;
    button.userdata = (void *)&windows;
    button.callback = window_type_callback;
    for (const auto &text : std::array<std::string, 3>({"NO", "HAN", "HAM"})) {

      button.text = text;

      radio_window_type.add(button);
      button.xpos += button.width + 1;
    }
    radio_window_type.select(WINDOW_NONE);

    button.text = "X";
    button.border = FG_BLACK;
    button.color = FG_GREY5;
    button.userdata = (void *)&finished;
    button.callback = quit_callback;
    button.width = 13;
    button.xpos = ScreenWidth() - button.width - 1;
    widgets.add(button);

    widgets.glgfx = this;
    widgets.add(radio_wave_type);
    widgets.add(radio_window_type);

    return true;
  }

  bool OnUserUpdate(float fElapsedTime) final {

    if (KeyUp('q'))
      finished = true;
    if (KeyUp('p'))
      bShowFPS = !bShowFPS;

    double f = 0.0;
    for (int k = 0; k < 16; k++) {
      if (KeyPressed("zsxcfvgbnjmk,l./"[k])) {
        f = f_base * pow(pow(2.0, 1.0 / 12), k);
      }
    }
    if (frequency != f)
      frequency = f;

    Clear(FG_BLACK);

    short p;

    size_t x0 = 0, y0 = 90, x1, y1, step_size = sample_size / ScreenWidth();
    for (size_t i = 0; i < sample_size; i++) {
      callback((double)i, &p, sizeof(short));
      sample[i] = static_cast<float>(p) * windows.window[i];
      if ((i % step_size) == 0) {
        x1 = i / step_size;
        y1 = 90 + 50 * (sample[i] / SHRT_MAX);
        DrawLine(x0, y0, x1, y1, FG_RED);
        x0 = x1;
        y0 = y1;
      }
    }
    fftwf_execute(plan);

    DrawString(8, 146, "dt =", FG_RED);
    DrawString(8 + 5 * 8, 146,
               std::to_string((1000 * sample_size) / samplerate), FG_RED);
    DrawString(8 + 5 * 8 + 5 * 8, 146, "ms", FG_RED);

    DrawLine(0, 160, ScreenWidth() - 1, 160);

    DrawString(180, 168, "Frequency", FG_GREEN);
    DrawString(180 + 10 * 8, 168, std::to_string((int)frequency), FG_GREEN);
    DrawString(180 + 10 * 8 + 4 * 8, 168, "Hz", FG_GREEN);

    float fft_max = 1.0f;
    for (size_t i = 1; i < ((sample_size >> 1) + 1); i++) {
      fft[i][0] = sqrtf(fft[i][0] * fft[i][0] + fft[i][1] * fft[i][1]);
      if (fft[i][0] > fft_max) {
        fft_max = fft[i][0];
      }
    }

    DrawLine(0, ScreenHeight() - 26, sample_min, ScreenHeight() - 26, FG_GREEN);
    for (int i = 1; i < (ScreenWidth() - (int)sample_min); i++) {
      DrawLine(i + sample_min, ScreenHeight() - 26, i + sample_min,
               ScreenHeight() - 26 - (int)(80.0f * fft[i][0] / fft_max),
               FG_GREEN);
    }
    DrawString(0, ScreenHeight() - 20, "0", FG_GREEN);
    DrawString(ScreenWidth() / 2 - 1, ScreenHeight() - 20,
               std::to_string(sample_min + ((ScreenWidth() - sample_min) / 2) *
                                               (sample_max - sample_min) /
                                               (sample_size / 2)),
               FG_GREEN);
    DrawString(ScreenWidth() - 32, ScreenHeight() - 20,
               std::to_string(sample_min + (ScreenWidth() - sample_min) *
                                               (sample_max - sample_min) /
                                               (sample_size / 2)),
               FG_GREEN);

    DrawLine(0, ScreenHeight() - 8, ScreenWidth() - 1, ScreenHeight() - 8);

    widgets.update();

    return !finished;
  }

  void Start() {
    cb::Audio::Start();
    cb::GLGFX::Start();
  }

protected:
  std::function<void(double, void *, size_t)> callback = [&](double dFrameTime,
                                                             void *buf,
                                                             size_t size) {
    for (size_t i = 0; i < size / sizeof(short); i++) {
      double t = (dFrameTime + (double)i) / (double)samplerate;
      switch (wave_type) {
      case WAVE_NOISE:
        ((short *)buf)[i] =
            (short)(SHRT_MAX *
                    (2.0 * ((double)rand() / (double)RAND_MAX) - 1.0));
        break;
      case WAVE_SQUARE:
        ((short *)buf)[i] =
            frequency > 0.0
                ? (sin(2.0 * frequency * M_PI * t) > 0.0 ? SHRT_MAX : SHRT_MIN)
                : 0;
        break;
      case WAVE_TRIANGLE:
        ((short *)buf)[i] =
            (short)(SHRT_MAX * asin(sin(2.0 * frequency * M_PI * t)) *
                    (2.0 / M_PI));
        break;
      case WAVE_SAW:
        ((short *)buf)[i] =
            frequency > 0.0
                ? (short)(SHRT_MAX * (2.0 / M_PI) *
                          (frequency * M_PI * fmod(t, 1.0 / frequency) -
                           (M_PI / 2.0)))
                : 0;
        break;
      case WAVE_SINE:
      default:
        ((short *)buf)[i] = (short)(SHRT_MAX * sin(2.0 * frequency * M_PI * t));
      }
    }
  };

private:
  cb::Widgets widgets;
  double frequency = 0.0;
  int wave_type = WAVE_SINE;
  bool finished = false;
  static constexpr const size_t sample_size = 2048;
  static constexpr const float f_base = 440.0f;
  Windows windows;
  float *sample;
  size_t sample_min = 0;
  size_t sample_max = 0;
  fftwf_complex *fft;
  fftwf_plan plan;
  static constexpr const char *plan_filename = "plan.fftwf";
};

bool wave_type_callback(cb::WidgetButton *button, void *userdata) {

  int *waveform = static_cast<int *>(userdata);

  if (button->text == "SIN") {
    *waveform = Synth::WAVE_SINE;
  } else if (button->text == "SQ") {
    *waveform = Synth::WAVE_SQUARE;
  } else if (button->text == "TRI") {
    *waveform = Synth::WAVE_TRIANGLE;
  } else if (button->text == "SAW") {
    *waveform = Synth::WAVE_SAW;
  } else if (button->text == "NOI") {
    *waveform = Synth::WAVE_NOISE;
  } else {
    return false;
  }

  return true;
}

bool window_type_callback(cb::WidgetButton *button, void *userdata) {

  Windows *w = static_cast<Windows *>(userdata);

  if (button->text == "NO") {
    w->window = w->ones;
  } else if (button->text == "HAN") {
    w->window = w->hanning;
  } else if (button->text == "HAM") {
    w->window = w->hamming;
  } else {
    return false;
  }

  return true;
}

bool quit_callback(cb::WidgetButton *button, void *userdata) {

  bool *finished = static_cast<bool *>(userdata);
  *finished = true;
  return true;
}

#endif // CBGLGFX_SYNTH_H
