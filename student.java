package 统计成绩;

	import java.util.*;

		public class student{
			private int STU_NUM=5;
			private int SUB_NUM=3;
			private String[][] data=new String[STU_NUM][SUB_NUM+2];
			public void HighestScore(String[][] original) {
				int flag=Integer.parseInt(original[0][4]);
				int position=0;
				for(int i=1; i<STU_NUM;i++) {
					if(flag<Integer.parseInt(original[i][4])) {
						flag=Integer.parseInt(original[i][4]);
						position=i;
					}
				}
		        System.out.print("最高分同学姓名和总分为:");
				System.out.println(original[position][0]+" "+original[position][4]);
			}
			public void LowestScore(String[][] original) {
				int flag=Integer.parseInt(original[0][4]);
				int position=0;
				for(int i=1; i<STU_NUM; i++) {
					if(flag>Integer.parseInt(original[i][4])) {
					flag=Integer.parseInt(original[i][4]);
					position=i;
					}
				}
				System.out.print("最低分同学姓名和总分为:");
				System.out.println(original[position][0]+" "+original[position][4]);
			}
			public void Sort(String[][] original) {
				String[][] result=original;
				String temp;
				int i,j;
				for( i=0; i<STU_NUM-1; i++) {
					for(j=i+1; j<STU_NUM; j++) {
						if(Integer.parseInt(original[i][4])<Integer.parseInt(original[j][4])) {
							temp=result[i][4];
							result[i][4]=result[j][4];
							result[j][4]=temp;
							temp=result[i][0];
							result[i][0]=result[j][0];
							result[j][0]=temp;
						}
					}
				}
				System.out.println("排名\t"+"姓名\t"+"总分\t");
				for(i=1; i<=STU_NUM; i++) {
					System.out.println(i+"\t"+result[i-1][0]+"\t"+result[i-1][4]);
				}
			}
			public void ScoreUnder60(String[][] original) {
				System.out.println("平均分在60分以下的同学的姓名为:");
				ArrayList<String> temp=new ArrayList<String>();
				for(int i=0; i<STU_NUM; i++) {
					if(Integer.parseInt(original[i][4])/SUB_NUM<60) {
						temp.add(original[i][0]);
					}
				}
				System.out.println(temp+" ");
				System.out.println("平均分在六十分之下的同学人数为:"+temp.size());
			}
			public Integer SearchScore(String name) {
				int position=-1;
				for(int i=0; i<STU_NUM;i++) {
					if(name.equals(data[i][0])) {
						position=i;
					}
				}
				if(position!=-1) {
					return Integer.valueOf(data[position][4]);
				}else {
					return -1;
				}
			}
			public int Operator(String order, Scanner s) {
				if("1".equals(order)) {
					HighestScore(data);
					LowestScore(data);
				}else if("2".equals(order)) {
					Sort(data);
				}else if("3".equals(order)) {
					ScoreUnder60(data);
				}else if("4".equals(order)) {
					String name;
					System.out.println("please enter the student's name:");
					name=s.nextLine();
					if(SearchScore(name)==-1) {
						System.out.println("查无此人");
					}else {
						System.out.println(name+"的总分为:"+SearchScore(name));
					}
				}else if("5".equals(order)) {
					return 0;
				}else {
					System.out.println("输入错误");
				}
				return 1;
			}
			public void InputData(Scanner s) {
				String name;
				int chinese_score, math_score, english_score;
				chinese_score=math_score=english_score=0;
				for(int i=1; i<=STU_NUM; i++) {
				  System.out.println("请输入第"+i+"个人的姓名:");
				  name=s.nextLine();
				  data[i-1][0]=name;
				  System.out.println("请输入第"+i+"个人的语文成绩:");
				  chinese_score=Integer.parseInt(s.nextLine());
				  System.out.println("请输入"+i+"个人的数学成绩:");
			      math_score=Integer.parseInt(s.nextLine());
				  System.out.println("请输入第"+i+"个人的英语成绩:");
				  english_score=Integer.parseInt(s.nextLine());
				  data[i-1][1]=String.valueOf(chinese_score);
				  data[i-1][2]=String.valueOf(math_score);
				  data[i-1][3]=String.valueOf(english_score);
				  data[i-1][4]=String.valueOf(chinese_score+math_score+english_score);
				}
			}
		}

