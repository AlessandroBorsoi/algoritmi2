# Grafi pesati e Dijkstra

Utilizzando il codice dei compiti precedenti, si sviluppi il codice per gestire un grafo diretto pesato upo_wdirgraph_t implementato con matrice di adiacenza (si noti che può essere facilmente modificato il codice già sviluppato per grafi non pesati) e calcolare un albero dei cammini minimi con l'algoritmo di Dijkstra cmDijkstra(upo_wdirgraph_t graph, int s). Non è necessario che tutte le funzioni implementate siano riscritte. Si mantengano solo le funzioni utili alla gestione del grafo (creazione, distruzione, inserimento/rimozione nodi e archi) ed all'esecuzione dell'algoritmo di Dijkstra. Non è necessario mantenere, ad esempio, le funzioni che calcolano le componenti fortemente connesse.

Considerate che l'algoritmo deve restituire sia i cammini trovati che i loro pesi. Avete principalmente 2 possibilità per farlo. La più facile è restituire una matrice di 2 righe e n colonne (o viceversa) che contenga in una riga il vettore dei padri/predecessori e nell'altra le distanze calcolate da Dijkstra. La più difficile è restituire un grafo pesato orientato (utilizzando upo_wdirgraph_t) che rappresenti l'albero dei cammini minimi. In questo caso, ovviamente, le distanze calcolate da Dijkstra non sono esplicitamente rappresentate nell'output, ma possono essere ricavate da esso.

La consegna deve contenere un programma di test interattivo che permetta di usare il codice sviluppato. Il codice deve essere commentato e le variabili devono avere nomi significativi.

La consegna deve essere contenuta in un file .zip e contenere un file README.txt con istruzioni per la compilazione ed esecuzione del codice e qualsiasi osservazione che si ritenga utile per descrivere il progetto.

La consegna deve inoltre comprendere qualsiasi file necessario per la compilazione.