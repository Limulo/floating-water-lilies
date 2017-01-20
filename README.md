# README

**floating water lilies** WIP.


## Over Head Controlled lilies (silent lilies)

Le ninfee ricevono comandi da una stazione di controllo master e **non** sono pensate per comunicare l'un l'altra. In tale caso la singola ninfeaa deve montare:
* ricevitore di luce infrarossa (come il [TSOP](http://www.robot-italy.com/en/tsop2236-ir-receiver-modules-for-remote-control-systems.html));

Il sistema **OHC** invece deve avere uno o più:
* LED ad infrarossi o trasmettitore ad infrarossi.


## Autonomous Chatty Lilies (w/o OHC)

Le ninfee sono agenti autonomi con comportamenti prestabiliti dal codice e reagiscono agli stimoli esterni senza bisogno di direttiva dal OHC. La comunicazione deve avvenire in ambo le direzioni. Sarà necessaio quindi fornire ciascuna ninfea di:

* trasmettitore IR (uno o più)
* ricevitore IR (uno o più)

Risolvere eventuali problemi di _crosstalk_.

## Autonomous Chatty Lilies w/ OHC

Questo caso differisci di poco rispetto al precedente. Si tratta infatti dell'unione delle prime due casistiche.
