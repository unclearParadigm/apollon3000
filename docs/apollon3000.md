# Apollon3000 CLI

a simple commandline interface to perform GPIO-Operations.

| Parameter             | Values                | Description                                       |
|:---------------------:|:---------------------:|:-------------------------------------------------:|
| -c --color            | rgb                   | which LEDs shall be lighted up                    |
| -b --blinkInterval    | value in milliseconds | Blink-Program with interval                       |
| -s --sweepActivated   | True or False         | addition to Blink, which dimms the selected LED   |
| -v --verbose          | True or False         | add additional Output to identify problems faster |
| -i --intensity        | value in percent      | Sets the Light-Intensity of a LED                 |

# Build-Example
```bash
cd src/apollon3000
# Add Exectuable permissions for Build-Script (needs to be done only once)
chmod +x build.sh
./build.sh
```

# Commandline-Examples

| Command                           | Description                                                                |
|:---------------------------------:|:--------------------------------------------------------------------------:|
| apollon3000 -c rg -b 2000         | let red and green LED blink in interval of 2 seconds (=2000 milliseconds)  |
| apollon3000 -c b -b 2000 -s       | let blue LED be dimmed from 0 to 100% in two seconds, and again back to 0% |
| apollon3000 -c rgb -i 50          | set all LEDs to intensity of 50%                                           |
| apollon3000 -c rgb -i 0           | turn off all LEDs                                                          |


