package 统计成绩;

import java.util.*;

public class score {
	    public static void main(String[] args) {
	        boolean end_flag=true;
	    	Scanner s=new Scanner(System.in);
	    	student stu=new student();
	        stu.InputData(s);
	        String order;
	        while(end_flag) {
	        	System.out.println("please choose:");
	        	System.out.println("1.最高分与最低分\n2.排序\n3.不及格\n4.查找\n5.退出");
	        	order=s.nextLine();
	        	if(stu.Operator(order,s)==0) {
	        		end_flag=false;
	        	}
	        }
	        s.close();
	    }
}
