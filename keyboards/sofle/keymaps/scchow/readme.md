A custom keymapping for the Sofle RGB v3.0.0 (mini-E LED version).

My build also uses Elite-Pi microcontrollers that uses the Raspberry Pi rp2040 instead Atmega32u4 of the standard Pro-Micro.

To build QMK for the rp2040, use the following:

```
qmk compile -kb sofle/rev1 -km scchow -e CONVERT_TO=promicro_rp2040
```

Auto Detection of Handedness
---

In config.h, instead of setting `#define MASTER_LEFT` or `#define MASTER_RIGHT`, one can encode handedness in EEPROM.
In `config.h`, uncomment `#define EE_HANDS` and comment out `#define MASTER_LEFT`/`#define MASTER_RIGHT`. 
Then flash each side with the corresponding commands:
```
 make sofle:scchow:uf2-split-right
```
and 
```
 make sofle:scchow:uf2-split-left
```
Left/Right should be written into EEPROM and should persist unless EEPROM is wiped.

# TODO: RGB Matrix Lighting

Relevant links:
- https://github.com/samhocevar-forks/qmk-firmware/blob/master/docs/feature_rgb_matrix.md
- https://www.reddit.com/r/olkb/comments/sbvefp/has_anyone_gotten_qmk_rgb_matrix_effects_working/


# Debugging Notes

### Can no longer wake computer up with keyboard

Somewhere in my debugging the on wake key stuck issue, I broke waking from sleep using this board. Would be nice to fix it.

Maybe try things [here](https://github.com/qmk/qmk_firmware/issues/1149#issuecomment-792042931).

1. Added `#define NO_SUSPEND_POWER_DOWN` to `config.h`.
    - Keyboard, leds, and OLEDs do not turn off, but keypresses do not wake up the computer.


 