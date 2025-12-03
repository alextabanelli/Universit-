/* ************************************************
 * Classe per testare gil algoritmi MST
 * 
 * Esempio di esecuzione:
 *
 * java MSTTest fileIn 
 * 
 * dove "fileIn" è il nome di un file che contiene la descrizione di un grafo non orientato pesato:
 * ad ogni riga del file si riportano gli indici di due nodi collegati da un arco e del relativo peso
 * separati da un TAB. 
 * NOTA: essendo il grafo non orientato, è sufficiente descrivere un arco una sola volta 
 * (ci pensa il programma a inserire due volte l'arco considerando separatamente
 * le due direzioni possibili)
 * 
 * Dopo aver letto il file, crea il grafo relativo, ne calcola il minimum spanning tree, poi
 * stampa il minimum spanning tree ed il relativo costo totale
 *
 * *************************************************/


import java.io.*;
import java.util.*;
import algorithm.graph.MST.*;
import datastructure.graph.*;


public class MSTTest {	
		
	/*
	* Main per leggere un file che reppresenta un grafo, calcolare il suo 
	* Minimum Spanning Tree e stamparlo
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
				g.addEdge(nodi.get(dst.get(j)),
					nodi.get(src.get(j)),pesi.get(j));
			}
			
			// Calcola il Minimum Spanning Tree
			MST<Integer> mst = new Kruskal<Integer>();
		    Graph<Integer> t = mst.MinimumSpanningTree(g);

			// Stampa il Minimum Spanning Tree ed il relativo costo
			ArrayList<Vertex<Integer>> vert = t.vertexes();
			for (int i=0; i<t.vertexNum(); i++) {
				System.out.println("Adiacenti a: "+(vert.get(i)).getData());
				ArrayList<Edge<Integer>> archi = t.outEdges(vert.get(i));
				for (int j=0; j<g.outDegree(vert.get(i)); j++) {
					System.out.print( "  "+ (archi.get(j)).getDest().getData()+" "+
						(archi.get(j)).getWeight() );
				}
				System.out.println();
			}
			double totPesi = 0;
			ArrayList<Edge<Integer>> e = t.edges();
			for (int i=0; i < e.size(); i++) totPesi = totPesi + e.get(i).getWeight();
			System.out.println("Costo tot: "+totPesi/2);
			
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
	
}
 
 
