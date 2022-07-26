all:
	pio -f -c vim run

upload:
	pio -f -c vim run --target upload

clean:
	pio -f -c vim run --target clean

program:
	pio -f -c vim run --target program

monitor:
	pio -f -c vim run --target monitor

uploadfs:
	pio -f -c vim run --target uploadfs

update:
	pio -f -c vim update

develop:
	pio -f -c vim run --target upload --target monitor