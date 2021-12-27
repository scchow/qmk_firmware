# scchow's GMMK Pro layout

This is the stock layout with the following modifications.

## Keymappings
- All keymappings set in [`keymap.c`](keymap.c)
- Layer 0:
  - `Print Screen (default)` 
    - Single Tap: Reset layers/caps lock
    - Double Tap: Toggle Caps Lock
- Layer 1: RGB/Reset Triggered by `FN`
  - `Reset_EEPROM` has been moved to `Esc`
  - RGB Keybindings see below
- Layer 2: Navigation, Triggered by `Caps Lock`, Double Tap to toggle
  - `Home`/`End` keys replaced with `Pg Up`/`Pg Dn`
  - Arrow keys are replaced with `Home`, `End`, `Pg Up`, `Pg Dn`
  - `IJKL` are also replaced with Arrow keys.
  - Pressing `Left/Right Shift` triggers `Caps Lock` 
- Layer 3: Flip Navigation, Triggered by holding `ALT` while on Layer 2
  - `IJKL` are also replaced with  `Home`, `End`, `Pg Up`, `Pg Dn`
- Layer 4/5: Same as Layers 2/3 except `HJKL` are used instead of `IJKL`
- Layer 6: Numpad mode, Triggered by Tap holding F12


## RGB
- RGB turns off after 30 minutes of inactivity - [`config.h`](config.h)
- RGB turns off when USB is suspended - [`config.h`](config.h)
- RGB Toggle on `FN`+`~` key
- RGB Plain, Breathe, Hue Breathe, Cycle all, Solid Reactive Multiwide, Multisplash, and Solid Multisplash effects on `FN`+`1`-`7` respectively
- RGB Cycle modes on `FN`+`TAB`
- RGB Hue Up/Down: `FN`+`Q`/`A`
- RGB Brightness Up/Down: `FN`+`W`/`S`
- RGB Speed Up/Down: `FN`+`E`/`D`
- Added `rgb.h` file that enumerates LEDs and contains common LED arrays.
- Added indicator lights for Layer 1/2/3 to indicate which keys have modified functions compared to default layer 0.
- Created custom RGB lighting modes in - [`rgb_matrix_user.inc`]
  - Custom Random Reactive Simple - Keys light up with random colors when pressed (`FN`+`8`)
  - Custom Solid Reactive Multiwide - Just testing to see if I understand how the code works (`FN`+`9`)
  - Turn off all Lighting modes but keep indicator lights (`FN`+`0`)

## Debounce
- Symmetric, Deferred, Per-key debounce algorithm (`sym_defer_pk`) - [`rules.mk`](rules.mk)
  - See [docs](https://beta.docs.qmk.fm/using-qmk/software-features/feature_debounce_type) for more details
