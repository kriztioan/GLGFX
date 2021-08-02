/**
 *  @file   Tetris.h
 *  @brief  Tetris in CBGLGFX
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef CBGLGFX_TETRIS_H_
#define CBGLGFX_TETRIS_H_

#include "../GLGFX.h"
#include "../SampledAudio.h"

#include <ctime>
#include <vector>
#include <sstream>
#include <iomanip>
#include <thread>
#include <fstream>

extern "C" size_t gameover_s;
extern "C" size_t gameover_sz;
extern "C" const char gameover_z[];

extern "C" size_t tada_s;
extern "C" size_t tada_sz;
extern "C" const char tada_z[];

extern "C" size_t bounce_s;
extern "C" size_t bounce_sz;
extern "C" const char bounce_z[];

extern "C" size_t tick_s;
extern "C" size_t tick_sz;
extern "C" const char tick_z[];

extern "C" size_t castle_s;
extern "C" size_t castle_sz;
extern "C" const char castle_z[];

extern "C" size_t taj_s;
extern "C" size_t taj_sz;
extern "C" const char taj_z[];

extern "C" size_t skyline_s;
extern "C" size_t skyline_sz;
extern "C" const char skyline_z[];

extern "C" size_t forest_s;
extern "C" size_t forest_sz;
extern "C" const char forest_z[];

extern "C" size_t island_s;
extern "C" size_t island_sz;
extern "C" const char island_z[];

extern "C" size_t wolf_s;
extern "C" size_t wolf_sz;
extern "C" const char wolf_z[];

class Tetris : public cb::GLGFX {

    static constexpr int nTetromino[][16] = {{ 0, 0, 0, 0,
                                                     0, 0, 0, 0,
                                                     0, 0, 0, 0,
                                                     0, 0, 0, 0},
                                             { 0, 0, 1, 0,
                                                     0, 0, 1, 0,
                                                     0, 0, 1, 0,
                                                     0, 0, 1, 0},
                                             { 0, 0, 0, 0,
                                                     0, 1, 1, 0,
                                                     0, 1, 1, 0,
                                                     0, 0, 0, 0},
                                             { 0, 0, 1, 0,
                                                     0, 1, 1, 0,
                                                     0, 0, 1, 0,
                                                     0, 0, 0, 0},
                                             { 0, 1, 0, 0,
                                                     0, 1, 0, 0,
                                                     0, 1, 1, 0,
                                                     0, 0, 0, 0},
                                             { 0, 0, 0, 0,
                                                     0, 1, 1, 0,
                                                     0, 0, 1, 1,
                                                     0, 0, 0, 0}};

    int nShape = 0;

    int nNextShape = 0;

    static constexpr int nFieldWidth = 12;

    static constexpr int nFieldHeight = 22;

    int *nField = nullptr;

    int nXpos = 0;

    int nYpos = 0;

    int nRotation = 0;

    float fTimer = 0.0;

    float fSpeed = 0.0;

    unsigned long nScore = 0;

    unsigned long nHighScore = 0;

    int nPixelSize = 0;

    std::vector< int > vLines;

    bool bGameOver = false;

    bool bFinished = false;

    bool bPaused = false;

    cb::SampledAudio audio;

    int nLineID = -1;

    int nBounceID = -1;

    int nTickID = -1;

    int nGameOverID = -1;

    std::vector< Bitmap *> vBackgrounds;

    unsigned long nBackgroundSelector = 0;

    float fBackgroundChanger = 0.0f;

    bool OnUserCreate() final {

        srand( time( nullptr ) );

        nField = new int[ nFieldWidth * nFieldHeight ];

        nPixelSize = 8;

        nLineID = audio.z_Load( tada_z, tada_sz, tada_s );

        nBounceID = audio.z_Load( bounce_z, bounce_sz, bounce_s );

        nTickID = audio.z_Load( tick_z, tick_sz, tick_s );

        nGameOverID = audio.z_Load( gameover_z, gameover_sz, gameover_s );

        audio.SetAudioSamplerate( 44100 );
        audio.SetAudioStereo( 2 );
        audio.SetAudioChannels( 32 );
        audio.SetBitsPerChannel( 8 );
        audio.SetVolume( 75 );
        audio.Start();

        vBackgrounds.push_back( z_LoadBitmap( castle_z, castle_sz, castle_s) );
        vBackgrounds.push_back( z_LoadBitmap( taj_z, taj_sz, taj_s) );
        vBackgrounds.push_back( z_LoadBitmap( skyline_z, skyline_sz, skyline_s) );
        vBackgrounds.push_back( z_LoadBitmap( forest_z, forest_sz, forest_s) );
        vBackgrounds.push_back( z_LoadBitmap( island_z, island_sz, island_s) );
        vBackgrounds.push_back( z_LoadBitmap( wolf_z, wolf_sz, wolf_s) );

        nBackgroundSelector = rand() % vBackgrounds.size();

        Reset();

        return true;
    }

    void OnUserDestroy() final {

        delete[] nField;

        for( auto &b : vBackgrounds ) FreeBitmap( b );
    }

    bool OnUserUpdate( float fElapsedTime ) final {

        fTimer += fElapsedTime;

        Input();

        Draw();

        if( bPaused ) return !bFinished;

        Logic();

        fBackgroundChanger += fElapsedTime;

        return !bFinished;
    }

    void Input() {

        if ( KeyDown( ' ' ) ) {
            if ( bGameOver ) {
                Reset();
                bGameOver = false;
            } else if( !bPaused && CheckMove(nXpos, nYpos, nRotation + 1 )) ++nRotation;
        }

        if( KeyUp( 'b' ) ) {

            nBackgroundSelector = ++nBackgroundSelector  % vBackgrounds.size();

            fBackgroundChanger = 0.0f;
        }

        if( !bGameOver && !bPaused && KeySpecialDown( GLUT_KEY_LEFT ) && CheckMove( nXpos - 1, nYpos, nRotation) ) --nXpos;
        if( !bGameOver && !bPaused && KeySpecialDown( GLUT_KEY_RIGHT ) && CheckMove( nXpos + 1, nYpos, nRotation ) ) ++nXpos;
        if( !bGameOver && !bPaused && KeySpecialDown( GLUT_KEY_DOWN ) && CheckMove( nXpos, nYpos + 1, nRotation ) ) ++nYpos;
        if( KeyUp( 'r' ) ) Reset();
        if( KeyUp( 'q' ) ) bFinished = true;
        if( KeyUp( 'p' ) ) bPaused = !bPaused;
    }

    void Draw() {

        DrawBitmap( *vBackgrounds[ nBackgroundSelector ], 0, 0, ScreenWidth(), ScreenHeight() );

        int nOffsetX = ( ScreenWidth() - nFieldWidth * nPixelSize ) / 2;

        int nOffsetY = ( ScreenHeight() - nFieldHeight * nPixelSize ) / 2;

        for( int x = 0; x < nFieldWidth; x++ ) {
            for ( int y = 0; y < nFieldHeight; y++ )
                DrawFilledRectangle(nOffsetX + x * nPixelSize, nOffsetY + y * nPixelSize, nOffsetX + ( x + 1 ) * nPixelSize - 1, nOffsetY + ( y + 1 ) * nPixelSize - 1, nField[ x + nFieldWidth * y ] );
        }

        for( int px = 0; px < 4; px++ ) {
            for (int py = 0; py < 4; py++)
                if ( nTetromino[ nShape ][ Rotate( px, py, nRotation ) ] > 0 )
                    DrawFilledRectangle( nOffsetX + ( nXpos + px ) * nPixelSize, nOffsetY + ( nYpos + py ) * nPixelSize, nOffsetX + (  nXpos + px + 1 ) * nPixelSize - 1, nOffsetY + ( nYpos + py + 1) * nPixelSize - 1, nShape ) ;
        }

        for( int px = 0; px < 4; px++ ) {
            for (int py = 0; py < 4; py++) {
                if( nTetromino[ nNextShape ][ px + py * 4 ] > 0 )
                    DrawFilledRectangle(nOffsetX + ( nFieldWidth + px ) * nPixelSize, nOffsetY + py * nPixelSize, nOffsetX + ( nFieldWidth + px + 1 ) * nPixelSize - 1, nOffsetY + ( py + 1 ) * nPixelSize - 1, nNextShape );
            }
        }

        std::stringstream ss;

        ss << "SCORE: " << std::setw( nFieldWidth - 7 ) << nScore;

        DrawString( nOffsetX, nOffsetY + ( nFieldHeight + 1 ) * nPixelSize, ss.str(), FG_GREY1 );

        ss.str( "" );

        ss << "HIGH : " << std::setw( nFieldWidth - 7 ) << nHighScore;

        DrawString( nOffsetX, nOffsetY + ( nFieldHeight + 2 ) * nPixelSize, ss.str(), FG_GREY1);

        ss.str( "" );

        ss << "SPEED: " << std::fixed << std::setprecision(1 ) << 1.0f / fSpeed;

        DrawString( nOffsetX, nOffsetY - 16, ss.str(), FG_GREY1);

        if( bGameOver ) DrawString( nOffsetX + nPixelSize, nOffsetY + ( nFieldHeight / 2 - 1 ) * nPixelSize, "GAME OVER!", FG_GREY1 );

        if( bPaused ) DrawString( nOffsetX + 3 * nPixelSize, nOffsetY + ( nFieldHeight / 2 - 1 ) * nPixelSize, "PAUSED", FG_MAROON );

    }

    void Logic() {

        if( fBackgroundChanger > 60.0f && !bGameOver ) {

            nBackgroundSelector = rand() % vBackgrounds.size();

            fBackgroundChanger = 0.0f;
        }

        if ( !vLines.empty() && fTimer >= ( fSpeed / 2 ) ) {

            audio.Play( nLineID, false );

            for( auto &py : vLines ) {
                for( int x = 1; x < ( nFieldWidth - 1 ); x++ )
                    for( int y = py; y > 1; y-- )
                        nField[ y * nFieldWidth + x ] = nField[ ( y - 1 ) * nFieldWidth + x ];
            }

            vLines.clear();
        }

        if( fTimer >= fSpeed && !bGameOver ) {

            if( CheckMove( nXpos, nYpos + 1, nRotation ) ) ++nYpos;
            else {

                for( int px = 0; px < 4; px++ ) {
                    for( int py = 0; py < 4; py++ )
                        if ( nTetromino[ nShape ][ Rotate( px, py, nRotation ) ] > 0 ) nField[ ( nXpos + px ) + ( nYpos + py ) * nFieldWidth ] = nShape;
                }

                for( int py = 0; py < 4; py++ ) {

                    if( nYpos + py < ( nFieldHeight - 1 ) ) {

                        bool bLine = true;

                        for( int x = 1; x < ( nFieldWidth - 1 ); x++ )
                            bLine &= ( nField[ x + ( nYpos + py ) * nFieldWidth ] > 0 );

                        if ( bLine ) {

                            vLines.emplace_back( nYpos + py );

                            for( int x = 1; x < ( nFieldWidth - 1 ); x++ )
                                nField[ x + ( nYpos + py ) * nFieldWidth ] = FG_LIME;
                        }
                    }

                    if( !vLines.empty() ) fSpeed -= 0.005;

                    nScore += ( 50 * vLines.size() ) * vLines.size();
                }

                nXpos = nFieldWidth / 2 - 2;

                nYpos = 1;

                nRotation = 0;

                nShape = nNextShape;

                nNextShape = 1 + ( rand() % 5 );

                if( !CheckMove( nXpos, nYpos, nRotation ) ) {

                    audio.Play( nGameOverID, false );
                    bGameOver = true;

                    if( nScore > nHighScore ) {

                        std::ofstream ofstr( ".tetris" );

                        if( ofstr.good() ) {

                            ofstr << nScore;

                            ofstr.close();
                        }
                    }
                }
            }

            fTimer = 0.0f;
        }
    }

    void Reset() {

        nXpos = nFieldWidth / 2 - 2;

        nYpos = 1;

        nRotation = 0;

        nShape = 1 + ( rand() % 5 );

        nNextShape = 1 + ( rand() % 5 );

        std::fill_n( nField,  nFieldWidth * nFieldHeight, 0 );

        for( int x = 0; x < nFieldWidth; x++ )
            for( int y = 0; y < nFieldHeight; y++ )
                if( x == 0 || y == 0 || x == ( nFieldWidth - 1 ) || y == ( nFieldHeight - 1 ) )
                    nField[ x + nFieldWidth * y ] = FG_GREY1;

        fTimer = 0.0f;

        fSpeed = 0.2f;

        std::ifstream ifstr(".tetris");
        if( ifstr.good() ) {
            ifstr >> nHighScore;
            ifstr.close();
        } else nHighScore = 0;

        nScore = 0;
    }

    bool CheckMove( int x, int y, int rotation ) {

        for( int px = 0; px < 4; px++ )
            for( int py = 0; py < 4; py++ )
                if( nTetromino[ nShape ][ Rotate( px, py, rotation ) ] > 0 &&
                    nField[ ( x + px ) + ( y + py ) * nFieldWidth ] > 0 ) {
                    audio.Play( nBounceID, false );
                    return false;
                }

        audio.Play( nTickID, false );
        return true;
    }

    static int Rotate( int x, int y, int rotation ) {

        int i = 0;

        switch ( rotation % 4  ) {
            case 0: i = y * 4 + x; break;
            case 1: i = 12 + y - ( x * 4 ); break;
            case 2: i = 15 - ( y * 4 ) - x; break;
            case 3: i = 3 - y + ( x * 4 );
        }

        return i;
    }

    bool OnUserResize() override { Clear( FG_GREY10 ); return true; }

public:

    Tetris() {

        bShowFPS = false;

        sTitle = "Tetris";
    };
};

#endif //CBGLGFX_TETRIS_H_
