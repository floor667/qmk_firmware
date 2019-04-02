/* Copyright 2016 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "musical_notes.h"

#ifndef SONG_LIST_H
#define SONG_LIST_H

#define NO_SOUND

#define ODE_TO_JOY                                          \
    Q__NOTE(_E4), Q__NOTE(_E4), Q__NOTE(_F4), Q__NOTE(_G4), \
    Q__NOTE(_G4), Q__NOTE(_F4), Q__NOTE(_E4), Q__NOTE(_D4), \
    Q__NOTE(_C4), Q__NOTE(_C4), Q__NOTE(_D4), Q__NOTE(_E4), \
    QD_NOTE(_E4), E__NOTE(_D4), H__NOTE(_D4),


#define GOODBYE_SOUND \
    Q__NOTE(_A4 ), \
    Q__NOTE(_AS4), \
    Q__NOTE(_B4 ), \
    HD_NOTE(_C5 ), 


#define AUDIO_ON_SOUND \
    E__NOTE(_A4 ),        \
    E__NOTE(_ES5),

#define AUDIO_OFF_SOUND \
    E__NOTE(_ES5),        \
    E__NOTE(_A4 ),


#define CAPS_LOCK_ON_SOUND \
    Q__NOTE(_CS4),          \
    E__NOTE(_D4 ),	   \
    E__NOTE(_GS4),

#define CAPS_LOCK_OFF_SOUND \
    Q__NOTE(_E4 ),           \
    E__NOTE(_D4 ),           \
    E__NOTE(_CS4),

#define CAPS_LOCK_ON_TWO \
    E__NOTE(_CS4),          \
    E__NOTE(_C4 ),           \
    ED_NOTE(_DS4),	   \
    E__NOTE(_GS4),	   \
    Q__NOTE(_F4 ),

#define CAPS_LOCK_OFF_TWO \
    E__NOTE(_AS4),	     \
    E__NOTE(_GS4),           \
    ED_NOTE(_G4 ),           \
    E__NOTE(_GS4),	   \
    Q__NOTE(_F4 ),

#define SCROLL_LOCK_ON_SOUND \
    E__NOTE(_GS4),            \
    E__NOTE(_G4 ),	\
    Q__NOTE(_AS4),	\
    E__NOTE(_C5 ),	\
    E__NOTE(_AS4),	\
    Q__NOTE(_CS5),

#define SCROLL_LOCK_OFF_SOUND \
    E__NOTE(_E4),             \
    E__NOTE(_D4),

#define NUM_LOCK_ON_SOUND \
    E__NOTE(_GS4),            \
    E__NOTE(_G4 ),	\
    Q__NOTE(_AS4),	\
    E__NOTE(_C5 ),	\
    E__NOTE(_AS4),	\
    Q__NOTE(_CS5),

#define NUM_LOCK_OFF_SOUND \
    E__NOTE(_CS5),          \
    Q__NOTE(_AS5),

#define AG_NORM_SOUND \
    E__NOTE(_A5),      \
    E__NOTE(_A5),

#define AG_SWAP_SOUND \
    SD_NOTE(_B5),      \
    SD_NOTE(_A5),      \
    SD_NOTE(_B5),      \
    SD_NOTE(_A5),

#define UNICODE_WINDOWS \
    E__NOTE(_B5),       \
    S__NOTE(_E6),

#define UNICODE_LINUX \
    E__NOTE(_E6),     \
    S__NOTE(_B5),

#define COIN_SOUND \
    E__NOTE(_A5  ),      \
    HD_NOTE(_E6  ),

#define ONE_UP_SOUND \
    Q__NOTE(_E6  ),  \
    Q__NOTE(_G6  ),  \
    Q__NOTE(_E7  ),  \
    Q__NOTE(_C7  ),  \
    Q__NOTE(_D7  ),  \
    Q__NOTE(_G7  ),

#define SONIC_RING \
    E__NOTE(_E6),  \
    E__NOTE(_G6),  \
    HD_NOTE(_C7),

#define ZELDA_PUZZLE \
    Q__NOTE(_G3),     \
    Q__NOTE(_FS4),    \
    Q__NOTE(_DS4),     \
    Q__NOTE(_A3),    \
    Q__NOTE(_GS3),     \
    Q__NOTE(_E4),     \
    Q__NOTE(_GS4),     \
    HD_NOTE(_C5),

#define ZELDA_TREASURE \
    E__NOTE(_A4 ), \
    E__NOTE(_AS4), \
    E__NOTE(_B4 ), \
    E__NOTE(_C5 ), \

#define TERM_SOUND \
    Q__NOTE(_CS5),  \
    E__NOTE(_D5 ),

#define OVERWATCH_THEME \
    HD_NOTE(_A4 ), \
    Q__NOTE(_E4 ), \
    Q__NOTE(_A4 ), \
    HD_NOTE(_B4 ), \
    Q__NOTE(_E4 ), \
    Q__NOTE(_B4 ), \
    W__NOTE(_CS5),

#define MARIO_THEME \
    Q__NOTE(_E5), \
    H__NOTE(_E5), \
    H__NOTE(_E5), \
    Q__NOTE(_C5), \
    H__NOTE(_E5), \
    W__NOTE(_G5), \
    Q__NOTE(_G4),

#define MARIO_GAMEOVER \
    HD_NOTE(_C5 ), \
    HD_NOTE(_G4 ), \
    H__NOTE(_E4 ), \
    H__NOTE(_A4 ), \
    H__NOTE(_B4 ), \
    H__NOTE(_A4 ), \
    H__NOTE(_AF4), \
    H__NOTE(_BF4), \
    H__NOTE(_AF4), \
    WD_NOTE(_G4 ),

#define MARIO_MUSHROOM \
    S__NOTE(_C5 ), \
    S__NOTE(_G4 ), \
    S__NOTE(_C5 ), \
    S__NOTE(_E5 ), \
    S__NOTE(_G5 ), \
    S__NOTE(_C6 ), \
    S__NOTE(_G5 ), \
    S__NOTE(_GS4), \
    S__NOTE(_C5 ), \
    S__NOTE(_DS5), \
    S__NOTE(_GS5), \
    S__NOTE(_DS5), \
    S__NOTE(_GS5), \
    S__NOTE(_C6 ), \
    S__NOTE(_DS6), \
    S__NOTE(_GS6), \
    S__NOTE(_DS6), \
    S__NOTE(_AS4), \
    S__NOTE(_D5 ), \
    S__NOTE(_F5 ), \
    S__NOTE(_AS5), \
    S__NOTE(_D6 ), \
    S__NOTE(_F6 ), \
    S__NOTE(_AS6), \
    S__NOTE(_F6 )

#define E1M1_DOOM  \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_D4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_C4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_BF3), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_B3 ), \
    Q__NOTE(_C4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_D4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_C4 ), \
    Q__NOTE(_E3 ), \
    Q__NOTE(_E3 ), \
    H__NOTE(_BF3),

#define RAISE \
    E__NOTE(_CS4), \
    Q__NOTE(_BF5), \
    E__NOTE(_B5 ), 

#define LOWER \
    E__NOTE(_BF5), \
    Q__NOTE(_D4 ), \
    E__NOTE(_CS4), 

#define EOCENE \
    E__NOTE(_G4 ), \
    H__NOTE(_BF4), \
    QD_NOTE(_CS5), \
    Q__NOTE(_E5 ), \
    ED_NOTE(_G5 ), \
    E__NOTE(_BF5), \
    QD_NOTE(_CS6),

#define EXECUTE \
    Q__NOTE(_CS4), \
    E__NOTE(_BF5), \
    E__NOTE(_B5 ), 

#endif
