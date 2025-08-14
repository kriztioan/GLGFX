/**
 *  @file   Audio.h
 *  @brief  MacOS Audio
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-07-30
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef CBGLGFX_AUDIO_H_
#define CBGLGFX_AUDIO_H_

#include <AudioUnit/AudioUnit.h>
#include <CoreAudio/CoreAudio.h>

#include <cstring>
#include <functional>
#include <utility>

#define VOLUME_RANGE (40) /* decibels */

inline OSStatus AudioRenderer_(void *inRefCon,
                               AudioUnitRenderActionFlags *ioActionFlags,
                               const AudioTimeStamp *inTimeStamp,
                               UInt32 inBusNumber, UInt32 inNumberFrames,
                               AudioBufferList *ioData);

namespace cb {
class Audio;
}

class cb::Audio {

public:
  ~Audio() {
    if (state)
      Stop();
  }

  [[maybe_unused]] void Start() {
    AudioComponentDescription desc;

    desc.componentType = kAudioUnitType_Output;
    desc.componentSubType = kAudioUnitSubType_DefaultOutput;
    desc.componentFlags = 0;
    desc.componentFlagsMask = 0;
    desc.componentManufacturer = kAudioUnitManufacturer_Apple;

    output_comp = AudioComponentFindNext(nullptr, &desc);
    if (!output_comp)
      return;
    if (AudioComponentInstanceNew(output_comp, &output_instance))
      return;
    if (AudioUnitInitialize(output_instance))
      return;

    AudioStreamBasicDescription streamFormat = {};
    UInt32 size = sizeof(AudioStreamBasicDescription);
    if (AudioUnitGetProperty(output_instance, kAudioUnitProperty_StreamFormat,
                             kAudioUnitScope_Input, 0, &streamFormat, &size))
      return;

    streamFormat.mSampleRate = samplerate;
    streamFormat.mFormatID = kAudioFormatLinearPCM;
    streamFormat.mFormatFlags = kAudioFormatFlagIsSignedInteger;
    streamFormat.mFramesPerPacket = 1;
    streamFormat.mChannelsPerFrame = stereo;
    streamFormat.mBitsPerChannel = bitsperchannel;
    streamFormat.mBytesPerFrame = bitsperchannel * stereo / 8;
    streamFormat.mBytesPerPacket = bitsperchannel * stereo / 8;

    if (AudioUnitSetProperty(output_instance, kAudioUnitProperty_StreamFormat,
                             kAudioUnitScope_Input, 0, &streamFormat,
                             sizeof(streamFormat)))
      return;

    AURenderCallbackStruct renderer;
    renderer.inputProc = AudioRenderer_;
    renderer.inputProcRefCon = this;

    if (AudioUnitSetProperty(output_instance,
                             kAudioUnitProperty_SetRenderCallback,
                             kAudioUnitScope_Output, 0, &renderer,
                             sizeof(AURenderCallbackStruct)))
      return;
    if (AudioOutputUnitStart(output_instance))
      return;

    state = true;
  };

  [[maybe_unused]] void Stop() {
    if (state) {
      AudioComponentInstanceDispose(output_instance);
      AudioOutputUnitStop(output_instance);
      state = false;
    }
  };

  [[maybe_unused]] inline void SetAudioSamplerate(unsigned int rate) {
    samplerate = rate;
  }

  [[maybe_unused]] inline void SetAudioStereo(unsigned int st) { stereo = st; }

  [[maybe_unused]] inline void SetBitsPerChannel(unsigned int b) {
    bitsperchannel = b;
  }

  [[maybe_unused]] inline void
  SetCallback(std::function<void(double, void *, size_t)> cb) {
    callback = std::move(cb);
  }

  OSStatus AudioRenderer(void *inRefCon,
                         AudioUnitRenderActionFlags *ioActionFlags,
                         const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber,
                         UInt32 inNumberFrames, AudioBufferList *ioData) {

    if (callback)
      callback(inTimeStamp->mSampleTime, ioData->mBuffers[0].mData,
               ioData->mBuffers[0].mDataByteSize);

    return noErr;
  }

  [[maybe_unused]] inline int GetVolume() {
    if (!state)
      return 0;
    float factor;
    AudioUnitGetParameter(output_instance, kHALOutputParam_Volume,
                          kAudioUnitScope_Output, 0, &factor);
    if (factor == 0.0)
      return 0;
    int volume = 100 + (int)(log10f(factor) * 20.0f * 100.0f / VOLUME_RANGE);
    return volume;
  }

  [[maybe_unused]] inline void SetVolume(int volume) {
    if (!state)
      return;
    float factor = (volume == 0)
                       ? 0.0f
                       : powf(10.0f, VOLUME_RANGE * ((float)volume - 100.0f) /
                                         100.0f / 20.0f);
    AudioUnitSetParameter(output_instance, kHALOutputParam_Volume,
                          kAudioUnitScope_Output, 0, factor, 0);
  }

  [[maybe_unused]] [[nodiscard]] inline bool good() const { return state; }

  [[maybe_unused]] [[nodiscard]] inline bool fail() const { return !state; }

protected:
  unsigned int samplerate = 22050;
  unsigned int stereo = 1;
  unsigned int bitsperchannel = 8;

private:
  AudioComponent output_comp;

  AudioComponentInstance output_instance;

  bool state = false;

  std::function<void(double, void *, size_t)> callback =
      [&](double dFrameTime, void *mData, size_t mDataByteSize) {
        bzero(mData, mDataByteSize);
      };
};

OSStatus AudioRenderer_(void *inRefCon,
                        AudioUnitRenderActionFlags *ioActionFlags,
                        const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber,
                        UInt32 inNumberFrames, AudioBufferList *ioData) {
  return static_cast<cb::Audio *>(inRefCon)->AudioRenderer(
      inRefCon, ioActionFlags, inTimeStamp, inBusNumber, inNumberFrames,
      ioData);
}

#endif // CBGLGFX_AUDIO_H_
