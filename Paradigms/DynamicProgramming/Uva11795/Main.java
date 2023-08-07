import java.io.*;
import java.util.*;
class Main{
  public static ArrayList<Long> dp;
  public static int busterWeapon;
  public static ArrayList<Integer> weapons;

  public static long solve(int mask,int n){
    if(mask == (1<<n)-1){
      return 1;
    }
    if(dp.get(mask) != -1){
      return dp.get(mask);
    }
    int weapon = busterWeapon;
    for(int i=0;i<n;i++){
      if( (mask & (1<<i)) > 0){
        weapon = weapon | weapons.get(i);
      }
    }
    long ans = 0;
    for(int i=0;i<n;i++){
      if((mask & (1<<i))==0 && (weapon & (1<<i))>0){
        ans = ans + solve(mask |(1<<i),n);
      }
    }
    dp.set(mask,ans);
    return ans;
  }

  public static void main(String args[]) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
		int cases = Integer.parseInt(br.readLine());
    for(int ci=1;ci<=cases;ci++){
      int n = Integer.parseInt(br.readLine());
      dp = new ArrayList<>();
      weapons = new ArrayList<>(n);
      for(int i=0;i<=(1<<n);i++){
        dp.add(-1L);
      }
      busterWeapon = 0;
      String aux = br.readLine();
      for(int i=0;i<n;i++){
        if(aux.charAt(i) == '1'){
          busterWeapon = busterWeapon | (1<<i);
        }
      }
      for(int i=0;i<n;i++){
        aux = br.readLine();
        int weaponI = 0;
        for(int j=0;j<n;j++){
          if(aux.charAt(j) == '1'){
            weaponI= weaponI | (1<<j);
          }
        }
        weapons.add(weaponI);
      }
      long ans = solve(0,n);
      pw.printf("Case %d: %d\n",ci,ans);



    }
    pw.close();
	}
}
