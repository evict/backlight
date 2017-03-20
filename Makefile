all:
	make kbd
	make backlight
kbd:
	gcc -DKBD backlight.c -o kbd
backlight:
	gcc -DBACKLIGHT backlight.c -o backlight
clean:
	rm -rf ./backlight
	rm -rf ./kbd
install:
	sudo chown root:root ./backlight
	sudo chmod 611 ./backlight
	sudo cp backlight /usr/local/bin/.
	sudo chmod +s /usr/local/bin/backlight
	sudo chown root:root ./kbd
	sudo chmod 611 ./kbd
	sudo cp kbd /usr/local/bin/.
	sudo chmod +s /usr/local/bin/kbd
uninstall:
	sudo rm /usr/local/bin/kbd
	sudo rm /usr/local/bin/backlight
