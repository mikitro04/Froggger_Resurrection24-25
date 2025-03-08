# 🐸 Frogger Resurrection - Gioco in C con ncurses

## 🎮 Introduzione  

**Frogger Resurrection** è una versione testuale del classico gioco arcade, sviluppata in **C** utilizzando la libreria **ncurses** per la gestione della grafica in modalità terminale.  

L'obiettivo del gioco è aiutare la rana ad attraversare la strada e il fiume per raggiungere le tane, evitando ostacoli come automobili e coccodrilli!  

🔹 **Sviluppato in collaborazione con Nicolò Loi**  

---

## 🔄 Due Versioni Disponibili  

Il gioco è disponibile in **due implementazioni**:  

1️⃣ **Versione con Processi** 🏗️  
   - Utilizza la creazione di **processi separati** per gestire i vari elementi del gioco.  
   - Maggiore isolamento tra le parti, ma più consumo di risorse.  

2️⃣ **Versione con Thread** 🔄  
   - Utilizza **thread concorrenti** per una gestione più leggera dei processi di gioco.  
   - Maggiore efficienza nell'uso delle risorse, ma con gestione della sincronizzazione.  

### 📂 Struttura dei File  

Entrambe le versioni condividono la seguente struttura di file:  

📦 Frogger Resurrection ┣ 📜 coccodrillo.c # Logica dei coccodrilli ┣ 📜 colors.c # Gestione dei colori ┣ 📜 colors.o
┣ 📜 funzioni.h # Header con funzioni condivise ┣ 📜 main.c # File principale ┣ 📜 menu.c # Gestione del menu di gioco ┣ 📜 print.c # Rendering con ncurses ┣ 📜 proiettile.c # Logica dei proiettili ┣ 📜 rana.c # Controllo della rana ┣ 📜 score.c # Sistema di punteggio ┣ 📜 start.c # Logica di avvio del gioco ┣ 📜 preProcessing.h # Pre-elaborazione delle risorse ┣ 📜 Makefile # Script per la compilazione ┣ 📜 frogger.out # Eseguibile del gioco ┣ 📜 resize.sh # Script di ridimensionamento (NON eseguibile di default) ┣ 📜 ctrResize.sh # Script di controllo del ridimensionamento (NON eseguibile di default) ┗ 📜 README.md # Questo file!

go
Copia
Modifica

⚠️ **Attenzione:**  
Di default, gli script `resize.sh` e `ctrResize.sh` **non sono eseguibili**. Per renderli eseguibili, usa:  

```sh
chmod +x resize.sh ctrResize.sh
```
🛠️ Installazione e Compilazione
🔹 Requisiti
Prima di iniziare, assicurati di avere:

Un sistema Linux/macOS con GCC installato
La libreria ncurses (libncurses-dev)
🔹 Compilazione ed Esecuzione
Apri un terminale nella cartella del progetto ed esegui:

```sh
make && ./frogger.out
```
Se vuoi pulire i file .o e l'eseguibile, usa:

```sh
make clean
```
🎮 Controlli di Gioco
Tasto	Azione
⬆️ **Freccia Su**	Salta in avanti; 
⬇️ **Freccia Giù**	Salta indietro; 
⬅️ **Freccia Sinistra**	Spostati a sinistra; 
➡️ **Freccia Destra**	Spostati a destra; 
❌ Q	Esci dal gioco.
