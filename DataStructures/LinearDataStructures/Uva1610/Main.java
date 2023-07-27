import java.io.*;
import java.util.*;
class Main{

	public static String f(String aux,String s,int ind){
		String ans = aux + s.charAt(ind);
		
		for(int i = ind+1;i<s.length();i++){
			if(i == s.length() - 1){
				ans += s.charAt(i);
				continue;
			}
			if(s.charAt(i) != 'Z'){
				ans += (char)(s.charAt(i) + 1);
				break;
			}else{
				ans += s.charAt(i);
			}
		}
		return ans;
	}
	
	public static String g(String aux,String t,int ind){
		String ans = aux;
		ans += t.charAt(ind);
		ind++;
		if(ind != t.length()){
			return ans;
		}
		for(int i=0;i<30;i++){
			ans += "x";
		}
		return ans;
	}
	
	public static void main(String args[]) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
		while(true){
			int num = Integer.parseInt(br.readLine());
			if(num == 0){
				break;
			}
			ArrayList<String> arr = new ArrayList<>(num);
			for(int i=0;i<num;i++){
				arr.add(br.readLine());
			}
			Collections.sort(arr);
			int mid = num/2;
			String s = arr.get(mid-1);;
			String t = arr.get(mid);
			String ans = "";
			int n = s.length(),m = t.length();
			int maxi = Math.max(n,m);
			for(int i=0;i<maxi;i++){
				if(i == n){
					break;
				}	
				char si = s.charAt(i);
				char ti = t.charAt(i);
				if(si == ti){
					ans += si;
					continue;
				}
				if((si+1) == ti){
					String a = f(ans,s,i);
					String b = g(ans,t,i);
					if(a.length() <= b.length()){
						ans = a;
					}else{
						ans = b;
					}
					break;
				}
				if(i + 1 == n){
					ans += si;
					break;
				}else{
					ans += (char)(si+1);
					break;
				}
			}
			pw.printf("%s\n",ans);
		}
		pw.close();
	}
}
