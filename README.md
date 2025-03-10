# 🐸 Frogger Resurrection - Gioco in C con ncurses

## 🎮 Introduzione  

**Frogger Resurrection** è una versione testuale del classico gioco arcade, sviluppata in **C** utilizzando la libreria **ncurses** per la gestione della grafica in modalità terminale.  

L'obiettivo del gioco è aiutare la rana ad attraversare la strada e il fiume per raggiungere le tane, evitando ostacoli come automobili e coccodrilli!  

🔹 **Sviluppato in collaborazione con Nicolò Loi**    https://github.com/G1MB0

---

## 🔄 Due Versioni Disponibili  

Il gioco è disponibile in **due implementazioni**:  

1️⃣ **Versione con Processi**   
   - Utilizza la creazione di **processi separati** per gestire i vari elementi del gioco.  
   - Maggiore isolamento tra le parti, ma più consumo di risorse.  

2️⃣ **Versione con Thread**   
   - Utilizza **thread concorrenti** per una gestione più leggera dei processi di gioco.  
   - Maggiore efficienza nell'uso delle risorse, ma con gestione della sincronizzazione.  

### 📂 Struttura dei File  

Entrambe le versioni condividono la seguente struttura di file:  

📦 Frogger Resurrection 
+ 📜 File C:
   - coccodrillo.c, main.c, print.c, rana.c, start.c, colors.c, menu.c, proiettile.c, score.c
+ 📜 File Header:
   - funzioni.h, preProcessing.h
+ 📜 File Bash:
   - ctrResize.sh, resize.sh

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
- ⬆️ **Freccia Su** Salta in avanti;
- ⬇️ **Freccia Giù** Salta indietro;
- ⬅️ **Freccia Sinistra** Spostati a sinistra;
- ➡️ **Freccia Destra** Spostati a destra;
- 💣 **Spazio** Spara due bombe a destra e a sinistra;
- ⏸️ **P** Metti in pausa il gioco;
- ▶️ **R** Riprendi il gioco;
- ❌ **Q** Esci dal gioco.
