# backlight
Easy (keyboard) backlight manipulation for Linux.

# Installation

Inside the `Makefile` replace the `BPATH` and `MPATH` variables for `BACKLIGHT` and/or `KBD` to the correct values. The current setting works for Macbook 11,1.
To find the correct files use the `find` tool as follows:

```
$ find . -name brightness
/sys/devices/pci0000:00/0000:00:02.0/backlight/acpi_video0/brightness
/sys/devices/pci0000:00/0000:00:02.0/drm/card0/card0-eDP-1/intel_backlight/brightness
/sys/devices/pci0000:00/0000:00:14.0/usb1/1-5/1-5:1.0/0003:05AC:025A.0001/input/input5/input5::kana/brightness
/sys/devices/pci0000:00/0000:00:14.0/usb1/1-5/1-5:1.0/0003:05AC:025A.0001/input/input5/input5::numlock/brightness
/sys/devices/pci0000:00/0000:00:14.0/usb1/1-5/1-5:1.0/0003:05AC:025A.0001/input/input5/input5::capslock/brightness
/sys/devices/pci0000:00/0000:00:14.0/usb1/1-5/1-5:1.0/0003:05AC:025A.0001/input/input5/input5::scrolllock/brightness
/sys/devices/pci0000:00/0000:00:14.0/usb1/1-5/1-5:1.0/0003:05AC:025A.0001/input/input5/input5::compose/brightness
/sys/devices/platform/applesmc.768/leds/smc::kbd_backlight/brightness
```

You can also choose to use `/sys/class/backlight/` and/or `/sys/class/leds/`. Both options work.
After setting the correct paths compile using `make`.

The binaries require SUID and needs to be owned by root.

# Usage

```
$ backlight
backlight [OPTIONS]

	-c	 display current setting
	-d	 decrease brightness
	-i	 increase brightness
```


