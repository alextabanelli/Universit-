/*
*
* Compilare con
*
* javac GraphVisitTest.java
*
* Eseguire con
*
* javac GraphVisitTest.java <FILENAME>
*
* FILENAME e' il nome di un file che contiene la descrizione di un grafo:
* ad ogni riga del file si riportano gli indici di due nodi collegati da un arco
* separati da un TAB. 
* Dopo aver letto il grafo, lo crea, lo stampa, effettua sia una BFS che una DFS 
* e stampa i risultati.
*/

import java.io.*;
import java.util.*;
import datastructure.graph.*;
import algorithm.graph.traversal.*;
	
public class GraphVisitTest {	
		
	public static void main( String[] args ) {
			
		try {
			
			long start_t, end_t, elapsed, min;
			double sec;
			
			File file = new File(args[0]);
			
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
			Graph<Integer> g = new GraphAL<Integer>();
			
			ArrayList<Vertex<Integer>> nodi = 
				new ArrayList<Vertex<Integer>>(max+1);
			for (int i=0; i<=max; i++)
				nodi.add(g.addVertex(i));
			for (int j=0; j<src.size(); j++) 
				g.addEdge(nodi.get(src.get(j)),
					nodi.get(dst.get(j)));
	
			System.out.println("GRAFO LETTO DA FILE");
			System.out.println(g.toString());
			
			/*ArrayList<Vertex<Integer>> vert = g.vertexes();
			for (int i=0; i<g.vertexNum(); i++) {
				System.out.println("Adiacenti a: "+(vert.get(i)).getData() );
				ArrayList<Edge<Integer>> archi = g.outEdges(vert.get(i));
				for (int j=0; j<g.outDegree(vert.get(i)); j++) {
					System.out.print( "  "+ ((archi.get(j)).getDest()).getData() );
				}
				System.out.println();
			}*/
			
			//versione BFS
			System.out.println("ALBERO DI VISITA BFS (vertice, padre nell'albero di visita)");
			Traversal<Integer> visBFS = 
				new BFS<Integer>();
			ArrayList<VisitedVertex<Integer>> l1 = visBFS.visit(g,nodi.get(0));
			for (int i=0; i<l1.size(); i++) {
				VisitedVertexBFS<Integer> vv = (VisitedVertexBFS<Integer>) l1.get(i);
				System.out.println( vv.getVertex().getData()+" "+
					((vv.getParent() != null) ? vv.getParent().getData() : -1)); 
			}	

			//versione DFS
			System.out.println();
			System.out.println("ALBERO DI VISITA DFS (vertice, padre nell'albero di visita, discovery time, finish time)");
			Traversal<Integer> visDFS = 
				new DFS<Integer>();
			ArrayList<VisitedVertex<Integer>> l2 = visDFS.visit(g,nodi.get(0));
			for (int i=0; i<l2.size(); i++) {
				VisitedVertexDFS<Integer> vv = (VisitedVertexDFS<Integer>) l2.get(i);
				System.out.println( vv.getVertex().getData()+" "+
					((vv.getParent() != null) ? vv.getParent().getData() : -1) +
					" "+vv.getDiscoveryTime()+" "+vv.getFinishTime());	
			}
						
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
	
}
 
 
