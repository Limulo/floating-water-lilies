# Progetto Luci in Acqua
 
## LUCE

[Qui](https://learn.adafruit.com/lets-put-leds-in-things/soldering?view=all) alcune idee sull'utilizzo di diversi metodi per illuminare da _Adafruit_.

### LED RGB

* [RobotItaly 1](http://www.gioblu.com/tutorials/sensori/59-sensore-prossimita-led)
* [RobotItaly 2](http://www.robot-italy.com/en/neopixel-jewel-7-x-ws2812-5050-rgb-led-with-integrated-drivers.html)
* [RobotItaly 3](http://www.robot-italy.com/en/2549-addressable-rgb-60-led-strip-5v-1m-ws2812b.html)

### Sensing della luce

* [Robot Italy](http://www.robot-italy.com/it/catalogsearch/result/?q=TCS34725)

### Elettroluminescenza

* [Adafruit](https://learn.adafruit.com/el-wire/soldering-to-el-wire)

## Comunicazione

### IR

* [protocolli, idee e progetti](http://www.epanorama.net/links/irremote.html) (da _Tom Igoe_);
* [555](http://www.robotroom.com/Infrared555.html), un grande ritorno. Un [semplice circuito](http://www.reconnsworld.com/ir_ultrasonic_basicirdetectemit.html) IR;
* IR by [Sparkfun](https://learn.sparkfun.com/tutorials/ir-communication);
* IR by [Adafruit](https://learn.adafruit.com/ir-sensor/overview)
* circuiti ed informazioni utili su [sb-projects](http://www.sbprojects.com/knowledge/ir/index.php)
* protocollo aperto [LIRC](http://www.lirc.org/)
* [Sony S-link](http://www.brian-patti.com/s-link/): risorse sul protocollo;
* libreria IR per Arduino [link1](https://github.com/z3t0/Arduino-IRremote) e [link2](http://z3t0.github.io/Arduino-IRremote/).

### Wireless

* [Articolo](http://ismanettoneblog.altervista.org/blog/lezione-12-comunicazioni-wireless-low-cost-arduino/?doing_wp_cron=1484755254.4665460586547851562500) su comunicazione WiFi con Arduino 
* [Articolo](http://pezzato.net/2013/07/arduino-wireless-economico-con-nrf24l01-plus.html) su trasmettitore WiFi con Arduino 
* [Quadricotteri](http://www.ted.com/talks/raffaello_d_andrea_the_astounding_athletic_power_of_quadcopters) Ted Talk "_Raffaello D'Andrea: The astounding athletic power of quadcopters_".
* protocollo [CSMA/CA](https://it.wikipedia.org/wiki/CSMA/CA).

## Hardware

### Gemma
* [GEMMA](https://www.adafruit.com/gemma) (vedi progetto [gufo](https://learn.adafruit.com/chirping-plush-owl-toy?embeds=allow))
* [Gemma - technicals](https://learn.adafruit.com/introducing-gemma/downloads) ([PDF](https://cdn-learn.adafruit.com/downloads/pdf/introducing-gemma.pdf) - a pagina 12 ci sono info e link per l'alimentazione)
* [FLORA + GEMMA](https://learn.adafruit.com/flora-and-gemma-isp) riprogrammazione bootloader con USBtiny di Adafruit (tutorial)
* [Gemma bootloader](https://github.com/adafruit/Adafruit-Trinket-Gemma-Bootloader)
* [VID e PID](http://www.usb.org/developers/vendor/) per prodotti USB
* [Gemma github - PCB](https://github.com/adafruit/Adafruit-Gemma-PCB)
* [Gemma github - Fritzing library](https://github.com/adafruit/Fritzing-Library)
* [MIC5225 - PDF](https://cdn-learn.adafruit.com/assets/assets/000/010/775/original/mic5225.pdf)
* [ATtiny85](http://www.atmel.com/devices/attiny85.aspx)

### Lilypad
* [Lilypad - overview](https://www.arduino.cc/en/Main/ArduinoBoardLilyPad)
* [schematics](https://www.arduino.cc/en/uploads/Main/LilyPad_schematic_v18.pdf)
* [getting started with Arduino Lilypad](https://www.arduino.cc/en/Guide/ArduinoLilyPad)
* [Programming bootloader](https://www.arduino.cc/en/Hacking/Programmer)
* [SparkFun accessories for lilypad](https://www.sparkfun.com/categories/135)

### Motori e movimento

* [link](https://learn.adafruit.com/vibro-bugz/materials?view=all) vibration bug by _Adafruit_;
* acquari, pompette, flusso d'acqua
* [cannone d'acqua](http://www.instructables.com/id/Squirt/): uno spunto da instructables.
* ricerca il termine **idrogetto** (tipologia di propulsione) o **waterJet** in inglese (anche se potrebbe essere confuso con il processo di taglio).
* alcune indicazioni utili sulla guid adi [motori](http://www.thebox.myzen.co.uk/Workshop/Motors_1.html) attraverso Arduino.

### Bootloader, programmazione ATmel
* istruzioni da [Adafruit](https://learn.adafruit.com/usbtinyisp?view=all)

### PCB, disegno e Stampa
* tutorials Sparkfun su [Eagle](https://www.sparkfun.com/search/results?term=eagle)
* [pcb trace calculator](http://circuitcalculator.com/wordpress/2006/01/31/pcb-trace-width-calculator/)

**Terminologia**

* [Gerber](https://en.wikipedia.org/wiki/Gerber_format) format;
* piano di massa
* solder mask
* silkscreen (serigrafia);

## Comportamento

### Prossimità

* [Articolo](http://www.gioblu.com/tutorials/sensori/176-sensore-ir-led-arduino-processing) su prossimità con LED IR
* [Articolo](http://www.gioblu.com/tutorials/sensori/59-sensore-prossimita-led) su prossimità con LED

### Reti neurali

* [Articolo](http://digitaljunky.io/playing-around-with-neural-networks-python-version/) sulle reti neurali in Python
* [Articolo](http://it.emcelettronica.com/?s=rete) sull'implementazione di una rete neurale in Simulink e Arduino

### Intelligenza Artificiale

* [Wikipedia](https://it.wikipedia.org/wiki/Intelligenza_artificiale)

### Automi cellulari

* [Wikipedia](https://it.wikipedia.org/wiki/Automa_cellulare)
* [post](https://blog.arduino.cc/2016/03/07/an-arduino-based-cellular-automata-with-oled-monitor/) sulla costruzione di un cellular automata con Arduino
* **Tribe bots** by [HackLab](http://dev.hacklabterni.org/projects/tribebot), ispirato all'originale [KiloBots](http://www.eecs.harvard.edu/ssr/projects/progSA/kilobot.html) di Harvard (un altro [link](https://www.kilobotics.com/)).
* Adafruit [Game of Life](https://learn.adafruit.com/game-of-life/preparation?embeds=allow&view=all)

### Self-organizing behaviours

* [harvard](http://www.eecs.harvard.edu/ssr/publications/)

## Spunti

* Bruce Munro's [works](http://www.brucemunro.co.uk/work/installations/);
* [Voyage](http://www.scottsdalepublicart.org/temporary-art/voyage) by [Aether and Hemera](http://www.aether-hemera.com/) per l'evento [Canal Convergence](http://scottsdalepublicart.org/events/canal-convergence-water-art-light-cycle-2#artists) - [project development blog](http://www.aether-hemera.com/Blog/2012/12/19?Id=Voyage__a_journey_into_imagination);
* [floating LED balls](http://www.catinwater.com/2012/09/04/100000-led-balls-floating-down-a-river-in-japan/)
* [Orbs Shaped Interactive Lighting Installation](http://forum.xcitefun.net/orbs-shaped-interactive-lighting-installation-t53441.html);

### from AADRL Spyropoulos Studio
* [CI Agents](http://drl.aaschool.ac.uk/portfolio/c-i-agents-2/)

![01](http://drl.aaschool.ac.uk/wp-content/uploads/2013/06/04-CIAgents.jpg)
![02](http://drl.aaschool.ac.uk/portfolio/c-i-agents-2/)
![03](http://drl.aaschool.ac.uk/wp-content/uploads/2013/06/01-CIAgents.jpg)
![04](http://drl.aaschool.ac.uk/wp-content/uploads/2013/06/05-CIAgents.jpg)

* [AntiBot](http://drl.aaschool.ac.uk/portfolio/anti-bot/)
* [vimeo video](https://vimeo.com/134977004)

## Approfondmenti

* [Sistemi complessi](https://it.wikipedia.org/wiki/Sistema_complesso)
* [Complessità](https://it.wikipedia.org/wiki/Epistemologia_della_complessit%C3%A0)
* [Comportamento Emergente](https://it.wikipedia.org/wiki/Comportamento_emergente)

### riferimenti PDF

* Robert Faludi, *Building wireless sensor networks*
* Luca Marchese, *RETI NEURALI SU PERSONAL COMPUTER + FUZZY LOGIC*
* A. Valeriani, F. Nassi, M. Maola, *Studio, implementazione e realizzazione di una rete neurale MLP riconfigurabile, processata tramite algoritmo di back propagation su scheda di sviluppo embedded Arduino Uno Rev.3*


