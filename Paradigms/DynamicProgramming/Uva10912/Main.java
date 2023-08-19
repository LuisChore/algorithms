import java.io.*;
import java.util.*;
class Main{
  public static ArrayList<ArrayList<ArrayList<Integer>>> dp;
  public static int solve(int index,int s,int l){
    if(l == 0){
      return (s == 0 ? 1 : 0);
    }
    if(dp.get(index).get(s).get(l) != -1){
      return dp.get(index).get(s).get(l);
    }
    int ans = 0;
    for(int i=index;i<=25;i++){
      if(i + 1 <=s){
        ans += solve(i+1,s-i-1,l-1);
      }
    }
    dp.get(index).get(s).set(l,ans);
    return dp.get(index).get(s).get(l);
  }

  public static void main(String args[]) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    StringTokenizer st = new StringTokenizer(br.readLine());
    int cases = 1;
    int S = 355,L = 30;
    dp = new ArrayList<>();
    for(int i=0;i<=26;i++){
      dp.add(new ArrayList<>());
      for(int j=0;j<=S;j++){
          dp.get(i).add(new ArrayList<>());
          for(int k=0;k<=L;k++){
            dp.get(i).get(j).add(-1);
          }
      }
    }
    while(true){
      int l = Integer.parseInt(st.nextToken());
      int s = Integer.parseInt(st.nextToken());
      if(l == 0 && s == 0){
        break;
      }
      if(l>26 || s > 351){
        pw.printf("Case %d: 0\n",cases);
      }else{
        int ans = solve(0,s,l);
        pw.printf("Case %d: %d\n",cases,ans);
      }
      st = new StringTokenizer(br.readLine());
      cases++;
    }
    pw.close();
	}
}
