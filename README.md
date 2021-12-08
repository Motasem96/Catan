# WiSe2021_Padi11
# Siedler von Catan Spiel


![alt text](https://github.com/Motasem96/Catan/blob/dev/Catan_Captures/1.PNG?raw=true)

![alt text](https://github.com/Motasem96/Catan/blob/dev/Catan_Captures/2.PNG?raw=true)

![alt text](https://github.com/Motasem96/Catan/blob/dev/Catan_Captures/2_1.PNG?raw=true)

![alt text](https://github.com/Motasem96/Catan/blob/dev/Catan_Captures/2_2.PNG?raw=true)

![alt text](https://github.com/Motasem96/Catan/blob/dev/Catan_Captures/3.PNG?raw=true)


## Ziel
### Muss:
    - 2D Implementierung von den grundlegenden Funktionen von dem Brettspiel, nach den Regeln die unten in Details beschrieben sind.
    
    - Einfache Animation, Audio, die das umgehen mit dem Spiel vereinfachen.
    
    - Das Spiel kann von mehreren Spielern auf dem selben lokalen Rechner gespielt werden.

    - Speichern von dem Spielstatus.

    - importieren von dem Spielstatus.
### kann:
    - einfache Chatfunktion (privat und public)
    - mehr Animation und die Möglichkeit über ein Netzwerk das Spiel zu spielen

### Nice to have:
    - mit Webassembly die C++ Funktionen importieren und in ein einfaches js oder ts Projekt implementieren
    - in einen Docker Container bauen und das Spiel ins Web deployen (advanced, wenn die Zeit das erlaubt)
    - Gegen den Rechner spielen können (Schwierigkeitslevels) mit künztlicher Intelligenz (Algorithmen)

## Spielteile:

## 1. Grenzen (6 Stück):

    - Numeriert (1,2)(2,3)….(6,1)
    - (1,2), (3,4), (5,6) haben jeweils 2 Zeichen
    - (2,3), (4,5), (6,1) haben jeweils ein Zeichen

## 2. Zahl/Buchstabe Punkte (18 Stück):

    - Jeder Punk hat auf der einen Seite einen Buchstaben
    - Auf der anderen Seite hat jeder Punkt eine Zahl
    - Die Zahlen sind entweder Rot oder dick-schwarz oder  normal schwarz markiert

***Die Zahlen die Rot markiert sind werden statistisch gesehen am häufigsten gewürfelt)*** 

## 3. Die Felderkarten:

	- Wald (4 Karten)
	- Getreidefeld (4 Karten)
	- Gras Feld mit Scharfen (4 Stück)
	- Lehm Karten (3 Stück)
	- Stein Karten (3 Stück)
	- Wüste (1 Stück)

## 4.	Informationskarten:
    - Baukosten Informationskarte(4 Stück):
    Enthält Informationen über die benötigten Karten aus der Bank um eine Straße, Siedlung, Stadt zu bauen oder eine Entwicklungskarte zu gewinnen.
    - Längste Handelsstraße
    - Größte Rittermacht
## 5.	Bank:
	Getreide
	Lehm
	Schärfe
	Holz
	Stein
	Entwicklungskarten(24 Stück):
	- Ritter(14 Karten)
	- Fortschritt(10 Stück):
	    - Monopol (2 Stück)
	    - Erfindung (2 Stück)
	    - Straßenbau(2 Stück)
	    - Bibliothek(1 Stück)
	    - Rathaus(1 Stück)
	    - Marktplatz(1 Stück)
	    - Kathedrale(1 Stück)
## 6.	Räuber (1 Stück)
## 7.	Würfel (2 Stück)
## 8.	Spielfiguren(4 Sets, 23 Figur pro Set):
	Siedlung (4 Stück)
	Stadt (5 Stück)
	Straße (14 Stück)

# Spielregeln:
## 1. Aufbau von dem Spielfeld:
    - Aufbau von der Grenze
    - Verteilung von den Spielfelder Karten (Zufällig)
    - Verteilung von den (Buchstaben/Nummern) Punkte nach Buchstaben dann umdrehen, um die Nummern aufzudecken (bis auf die Wüste)
	- Auf dem Feld von der Wüste kommt der Räuber am Anfang
	- Jeder Spieler bekommt eine der Farben und die entsprechenden Spielfiguren
## 2. Erste Runde:
    - Alle Spieler würfeln 
    - Der Spieler mit dem höchsten Würfelzahl darf mit dem Spiel anfangen und die erste Stadt und die erste Straße bauen
    - Städte dürfen nur an den Ecken von den Spielfeldern gebaut werden und müssen mindesten 2 Spielfelder Seiten aus einer anderen Stadt entfernt sein.
    - Die erste Spielrunde befindet sich im Uhrzeigersinn und jeder Spieler baut seine erste Stadt und Straße.

## 3. Spielsbeginn:
    - Alle anderen Spielrunden befinden sich gegen den Uhrzeigersinn 
	- Nach der ersten Runde kann Der letzte Spieler mit dem Spiel anfangen und würfeln
    - Alle Spieler die Felder besitzen mit der Zahl, die gewürfelt wurde bekommen entsprechende Karten von der Bank
    - Das Spiel geht weiter und jeder Spieler darf (in seiner Runde) etwas bauen wenn der Spieler das sich leisten kann (laut der Bauinformationskarte): 
        • Straße: Ein Holz und ein Lehm
        • Siedlung: Ein Holz, ein Lehm, ein Getreide und ein Scharf
        • Stadt: Zwei Getreide und 3 Steine
        • Entwicklungskarte: Ein Getreide, ein Scharf und ein Stein

    - Der Spieler mit der längsten Straße darf die entsprechende Karte behalten bis einer diese Eigenschaft diesem Spieler entziehen kann (Der Spieler mit dieser Karte bekommt 2 Siegpunkte)
    - Der Spieler mit den höchstens  (mindestens 3) Ritterkarten bekommt die größte Rittermacht Karte.
    - Eine Stadt darf mit einer Siedlung umgetauscht werden und nicht erst gebaut werden
	- Die Siegerpunkte eines Spielers lassen sich berechnen in dem man die Summe aller Siegpunkte zusammenaddiert, die ein Spieler sich erarbeitet hat:
        • Längste Straße: 2 Siegpunkte
        • Siedlung: 2 Siegpunkte
        • Stadt: 1 Siegpunkt
        • Größte Rittermacht: 2 Siegpunkte
## 4. Spielend:
    Das Spiel ist beendet und quasi gewonnen von dem Spieler, der als erstes 10 Siegpunkte erreicht hat.
## 5. Kartenumtausch:
    In jeder Runde dürfen Spieler unter einander Kartentauchen, so lang sie sich auf einen Deal geeignet haben.
## 6. 4-Karten Regel:
    - Jeder Zeit dürfen Spieler eine Karte aus der Bank nehmen und dagegen 4 beliebige Karten in die Bank zurücklegen.
## 7. Grenzenregel:
    - Falls ein Spieler eine Stadt oder eine Siedlung an der Grenze von dem Spielfeld sich gebaut hat, da wo ein Zeichen gibt, darf er/sie nach diesem Zeichnen Karten umtauschen:
        - 3:1, 3 beliebige Karten gegen eine gewünschte Karte aus der Bank umtauschen
        - ??
## 8. Räuber Regeln:
    1. Wenn ein Spieler 7 würfeln sollte, darf der Spieler den Räuber umplatzieren und da hinstellen wo er möchte aber nicht auf die Wüste.
    2. Wenn die Umplatzierung von dem Räuber stattfindet muss jeder Spieler, der über 7 Karten hat die Hälfte der Karten (aufgerundet zu seinem Vorteil) abgeben und die Bank zurücklegen und der Spieler, der gewürfelt hat darf eine zufällige Karte von dem nächsten Spieler abziehen.
    3. Wenn der Räuber auf einem Spielfeld steht, das nicht Wüste ist, verhindert den Feldbesitzer von seinem Feld zu profitieren, wenn die Zahl im Spiel vorkommen sollte.
