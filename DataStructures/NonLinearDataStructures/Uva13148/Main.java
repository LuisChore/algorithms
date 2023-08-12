import java.io.*;
import java.util.*;
class Main{
  public static boolean isSquare(int value){
    int low = 1,high = 10000;
    boolean ok = false;
    while(low<=high){
      int mid = (low + high)>>1;
      if(mid*mid ==value){
        ok = true;
        break;
      }
      if(mid*mid < value){
        low = mid + 1;
      }else{
        high = mid - 1;
      }
    }
    return ok;
  }
  public static boolean isCube(int value){
    int low = 1,high = 500;
    boolean ok = false;
    while(low<=high){
      int mid = (low + high)>>1;
      if(mid*mid*mid ==value){
        ok = true;
        break;
      }
      if(mid*mid*mid < value){
        low = mid + 1;
      }else{
        high = mid - 1;
      }
    }
    return ok;
  }

  public static void main(String args[]) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
		int value = Integer.parseInt(br.readLine());
    while(value != 0){
      if(isSquare(value) && isCube(value)){
        pw.printf("Special\n");
      }else{
        pw.printf("Ordinary\n");
      }
      value = Integer.parseInt(br.readLine());
    }
    pw.close();
	}
}
