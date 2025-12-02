/* ************************************************
 * Classe per testare gli algoritmi di ricerca dei single-source shortest paths
 * 
 * Esempio di esecuzione:
 *
 * java ShortestPathTest fileIn 
 * 
 * dove "fileIn" è il nome di un file che contiene la descrizione di un grafo orientato pesato:
 * ad ogni riga del file si riportano gli indici di due nodi collegati da un arco e del relativo peso
 * separati da un TAB. 
 * 
 * Dopo aver letto il file, crea il grafo relativo, ne calcola i cammini minimi da singole sorgente
 * considerando il prigmo vertice, poi stampa le distanze dei vertici dalla sorgente
 *
 * *************************************************/


import java.io.*;
import java.util.*;
import datastructure.graph.*;
import algorithm.graph.SSSP.*;

public class ShortestPathTest {	
		
	/*
	* Main per leggere un file che reppresenta un grafo e calcolare i cammini minimi
	* a partire dal primo vertice
	*/	
	public static void main( String[] args ) {
			
		try {
			
			long start_t, end_t, elapsed, min;
			double sec;
			
			File file = new File(args[0]);
			
			// Legge gli archi dal fileIn inserendo i vertici sorgente, i vertici
			// destinazione e i pesi in tre ArrayList src, dest e pesi, rispettivamente
			
			BufferedReader br = new BufferedReader(new FileReader(file));
			ArrayList<Integer> src = new ArrayList<Integer>();
			ArrayList<Integer> dst = new ArrayList<Integer>();
			ArrayList<Double> pesi = new ArrayList<Double>();
			String st,strest;
			int max=0,s,d,v,v2;
			double p;
			while ((st = br.readLine()) != null) {
				v = st.indexOf("\t");
				s = Integer.valueOf(st.substring(0,v));
				strest = st.substring(v+1);
				v2 = strest.indexOf("\t");
				d = Integer.valueOf(strest.substring(0,v2));
				p = Double.valueOf(strest.substring(v2+1));
				if (s>max) max=s;
				if (d>max) max=d;
				src.add(s);
				dst.add(d);
				pesi.add(p);
			}
			
			// Crea il relativo grafo
			Graph<Integer> g = 
				new GraphAL<Integer>();

			ArrayList<Vertex<Integer>> nodi = 
				new ArrayList<Vertex<Integer>>(max+1);
			for (int i=0; i<=max; i++)
				nodi.add(g.addVertex(i));
			for (int j=0; j<src.size(); j++) {
				g.addEdge(nodi.get(src.get(j)),
					nodi.get(dst.get(j)),pesi.get(j));
			}			
			
			// Calcola i camminimi minimi dal primo vertice
			SSSP<Integer> cammini;
			Map<Vertex<Integer>,Edge<Integer>> parent;
				
			cammini = new BellmanFord<Integer>();
			parent = cammini.SingleSourceShortestPaths(g, nodi.get(0));
			
			// Stampa le distanze dei vertici dalla sorgente
			for (int i=0; i<nodi.size(); i++) {
				System.out.println( "Distanza nodo " + nodi.get(i).getData() + " : " +
					computeDist(parent,nodi.get(i),nodi.get(0)) );
			}
			
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
	
	// Calcola la distanza di un vertice v da s considerando l'albero dei cammini minimi da s rappresentato da parent
	private static double computeDist(Map<Vertex<Integer>,Edge<Integer>> parent, Vertex<Integer> v, Vertex<Integer> s) {
		if (v!=s && parent.get(v) == null) return Double.POSITIVE_INFINITY;
		int d = 0;
		while (v != s) {
			d += parent.get(v).getWeight();
			v = parent.get(v).getSource();
		}
		return d;
	}
	
}
 
 
