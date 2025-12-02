/* ************************************************
 * Classe per testare le strutture Graph
 *
 * Esempio di esecuzione:
 *
 * java GraphTest fileIn 
 *
 * dove "fileIn" è il nome di un file che contiene la descrizione di un grafo:
 * ad ogni riga del file si riportano gli indici di due nodi collegati da un arco
 * separati da un TAB. 
 * Dopo aver letto il file, crea il grafo relativo, lo stampa, cancella il primo 
 * arco del primo vertice, ristampa, cancella il primo vertice e infine ristampa
 * il grafo nella sua struttura finale. 
 *
 * *************************************************/


import java.io.*;
import java.util.*;
import datastructure.graph.*;

public class GraphTest {	
	
	/*
	* Main per leggere un file che reppresenta un grafo e stamparlo
	* prima e dopo aver apportato alcune modifiche
	*/	
	public static void main( String[] args ) {
			
		try {
			
			long start_t, end_t, elapsed, min;
			double sec;
			
			File file = new File(args[0]);
			
			// Legge gli archi dal fileIn inserendo i vertici sorgente e i vertici
			// dfestinazione in due ArrayList src e dest, rispettivamente
			
			BufferedReader br = new BufferedReader(new FileReader(file));
			ArrayList<Integer> src = new ArrayList<Integer>();
			ArrayList<Integer> dst = new ArrayList<Integer>();
			String st;
			int max=0,s,d,v;
			while ((st = br.readLine()) != null) {
				v = st.indexOf("\t");
				s = Integer.valueOf(st.substring(0,v));
				d = Integer.valueOf(st.substring(v+1));
				if (s>max) max=s;
				if (d>max) max=d;
				src.add(s);
				dst.add(d);
			}
			
			// Crea il relativo grafo
			Graph<Integer> g = 	new GraphAL<Integer>();
			ArrayList<Vertex<Integer>> nodi = 
				new ArrayList<Vertex<Integer>>(max+1);
			for (int i=0; i<=max; i++)
				nodi.add(g.addVertex(i));
			for (int j=0; j<src.size(); j++) 
				g.addEdge(nodi.get(src.get(j)),
					nodi.get(dst.get(j)));
			
			// Stampa il grafo
			System.out.println(g.toString());
			
			// Rimuove il primo arco del primo vertice e ristampa il grafo
			System.out.println("Remove the first edge of the first vertex");
			ArrayList<Edge<Integer>> a = g.outEdges(nodi.get(0));
			g.removeEdge(a.get(0));
			System.out.println(g.toString());
			
			// Rimuove il primo vertice e ristampa il grafo
			System.out.println("Remove the first vertex");
			g.removeVertex(nodi.get(0));
			System.out.println(g.toString());

		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
	
}
 
 
