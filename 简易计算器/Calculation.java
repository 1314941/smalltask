package Calculator;

import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.Frame;
import java.awt.GridLayout;
import java.awt.Panel;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class Calculation {
	double num1, num2;
	String operator;
	boolean is_sqrt = false;
	boolean unfinished = false;
	Frame frame = new Frame("计算器  一次输入一个运算符");
	TextField inputBox = new TextField(40);
	Button[] button = new Button[20];

	Calculation() {
		frame.setBounds(200, 300, 500, 500);
		inputBox.setText(" ");
		frame.add(inputBox, BorderLayout.NORTH);
		Panel panel = new Panel();
		panel.setLayout(new GridLayout(5, 4, 3, 3));
		String[] s = { "sqrt", "<-", "AC", "%", "7", "8", "9", "+", "4", "5", "6", "-", "1", "2", "3", "*", "0", ".",
				"=", "/" };
		for (int i = 0; i < s.length; i++) {
			button[i] = new Button(s[i]);
			button[i].addActionListener(new ActionListen());
			panel.add(button[i]);
		}
		frame.add(panel, BorderLayout.CENTER);
		frame.setVisible(true);
		frame.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
	}

	public String division(double n1, double n2) {
		if (n2 == 0) {
			return "false";
		} else {
			return String.valueOf(n1 / n2);
		}
	}

	public class ActionListen implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			String label = e.getActionCommand();
			if (label.equals("=")) {
				unfinished = false;
				if (!is_sqrt) {
					num2 = Double.parseDouble(inputBox.getText());
				}
				is_sqrt = false;
				switch (operator) {
				case "+" -> inputBox.setText(num1 + num2 + " ");
				case "-" -> inputBox.setText(num1 - num2 + " ");
				case "*" -> inputBox.setText(num1 * num2 + " ");
				case "/" -> // 有问题
					inputBox.setText(division(num1, num2) + " ");
				case "%" -> inputBox.setText(num1 % num2 + " ");
				case "sqrt" -> inputBox.setText(Math.sqrt(num1) + " ");
				}
			} else if (label.equals("+") || label.equals("-") || label.equals("*") || label.equals("/")
					|| label.equals("sqrt") || label.equals("%")) {
				num1 = Double.parseDouble(inputBox.getText());
				inputBox.setText(num1 + " " + label);
				operator = e.getActionCommand();
				if (label.equals("sqrt")) {
					is_sqrt = true;
				}
				unfinished = false;
			} else if (label.equals("-")) {
				if (unfinished) {
					num1 = Double.parseDouble(inputBox.getText());
					inputBox.setText(num1 + " " + label);
					operator = e.getActionCommand();
					unfinished = false;
				} else {
					inputBox.setText("-"); // 此处有问题,不能一开始就输入负号
				}
			} else if (label.equals("<-"))

			{
				String expression = inputBox.getText();
				if (expression.length() != 0) {
					expression = expression.substring(0, expression.length() - 1);
					inputBox.setText(expression);
				}
			} else if (label.equals("AC")) {
				inputBox.setText(" ");
				unfinished = false;
			} else {
				String s = inputBox.getText();
				if (unfinished) {
					inputBox.setText(s + label);
				} else {
					inputBox.setText(label);
				}
				unfinished = true;
			}
		}

	}

	public static void main(String[] args) {
		new Calculation();
	}
}
