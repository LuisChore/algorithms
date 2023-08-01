import java.io.*;
import java.util.*;
class Main{
	public static void main(String args[]) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
		int cases = Integer.parseInt(br.readLine());
		while(cases-- > 0){
			String blank = br.readLine();
			TreeMap<Integer,Integer> Shared = new TreeMap<>();
			TreeSet<Integer> Blocked = new TreeSet<>();
			TreeMap<Integer,Integer> Exclusived = new TreeMap<>();
			TreeMap<Integer,Integer> timesShared = new TreeMap<>();
			while(true){
				StringTokenizer st = new StringTokenizer(br.readLine());
				String mode = st.nextToken();
				if(mode.equals("#") == true){
					break;
				}
				int trId = Integer.parseInt(st.nextToken());
				int dataId = Integer.parseInt(st.nextToken());
				if(Blocked.contains(trId)){
					pw.printf("IGNORED\n");
					continue;
				}
				if(Exclusived.containsKey(dataId)){
					int	 value = Exclusived.get(dataId);
					if(value == trId){
						pw.printf("GRANTED\n");
					}else{
						pw.printf("DENIED\n");
						Blocked.add(trId);
					}
					continue;
				}
				if(Shared.containsKey(dataId) && mode.equals("X")){
					if(timesShared.get(dataId) == 1 && Shared.get(dataId) == trId){
						Exclusived.put(dataId,trId);
						pw.printf("GRANTED\n");
					}else{
						Blocked.add(trId);
						pw.printf("DENIED\n");
					}
					continue;
				}
				if(Shared.containsKey(dataId)){
					if(Shared.get(dataId) != trId){
						int oldCounter = timesShared.get(dataId);
						timesShared.put(dataId,oldCounter + 1);
						Shared.put(dataId,trId);
					}
					pw.printf("GRANTED\n");
					continue;
				}
				if(mode.equals("X")){
					Exclusived.put(dataId,trId);
					pw.printf("GRANTED\n");
				}else{
					Shared.put(dataId,trId);
					timesShared.put(dataId,1);
					pw.printf("GRANTED\n");
				}
			}
			if(cases > 0){
				pw.printf("\n");
			}
		}
		pw.close();
	}
}
