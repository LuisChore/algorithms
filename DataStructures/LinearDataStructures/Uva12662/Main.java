import java.io.*;
import java.util.*;

class Main{
	private static final int INF_INT = 100000000;
	public static void main(String args[]) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
		int n = Integer.parseInt(br.readLine());
		ArrayList<String> v = new ArrayList<>(n);
		StringTokenizer st = new StringTokenizer(br.readLine());
		for(int i=0;i<n;i++){
			v.add(st.nextToken());
		}
		ArrayList<Integer> ans = new ArrayList<>(n);
		ArrayList<Integer> d = new ArrayList<>(n);
		for(int i=0;i<n;i++){
			ans.add(0);
			d.add(0);
		}
		int last = INF_INT;
		for(int i=0;i<n;i++){
			if(v.get(i).equals("?") == false){
				ans.set(i,0);
				last = 0;
			}else{		
				last++;
				d.set(i,last);
			}
		}
		last = INF_INT;
		for(int i=n-1;i>=0;i--){
			if(v.get(i).equals("?") == false){
				last = 0;
			}else{
				last++;
				if(last<d.get(i)){
					d.set(i,last);
					ans.set(i,1); // left of
				}else if(last > d.get(i)){
					ans.set(i,2); // right of
				}else{
					ans.set(i,3);
				}
			}
		}
		int q = Integer.parseInt(br.readLine());
		while(q-- > 0){
			int qi = Integer.parseInt(br.readLine());
			qi--;
			int value = ans.get(qi);
			if(value == 0){
				pw.printf("%s\n",v.get(qi));
			}else if(value == 1){
				for(int i=0;i<d.get(qi);i++){
					pw.printf("left of ");
				}
				pw.printf("%s\n",v.get(qi + d.get(qi)));
			}else if(value == 2){
				for(int i=0;i<d.get(qi);i++){
					pw.printf("right of ");
				}
				pw.printf("%s\n",v.get(qi - d.get(qi)));
			}else{
				pw.printf("middle of %s and %s\n",v.get(qi-d.get(qi)),v.get(qi+d.get(qi)));
			}
		}
		pw.close();
	}
}
