package com.qst.dms.ui;

import java.awt.Color;
import java.awt.EventQueue;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.border.EmptyBorder;

import com.qst.dms.entity.User;
import com.qst.dms.service.UserService;

public class LoginFrame extends JFrame {

	private static final long serialVersionUID = 1L;
	private JPanel contentPane;
	private JTextField name;
	private JTextField pwd;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					LoginFrame frame = new LoginFrame();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public LoginFrame() {
		setBackground(new Color(255, 255, 255));
		setForeground(new Color(255, 255, 128));
		setFont(new Font("Britannic Bold", Font.PLAIN, 12));
		setTitle("登录");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));

		setContentPane(contentPane);
		contentPane.setLayout(null);

		JLabel name_l = new JLabel("用户名 ：");
		name_l.setBounds(55, 68, 82, 21);
		contentPane.add(name_l);

		name = new JTextField();
		name.setBounds(112, 68, 191, 21);
		contentPane.add(name);
		name.setColumns(10);

		JLabel pwd_l = new JLabel("密码 :");
		pwd_l.setBounds(55, 131, 58, 15);
		contentPane.add(pwd_l);

		pwd = new JTextField();
		pwd.setBounds(112, 128, 191, 21);
		contentPane.add(pwd);
		pwd.setColumns(10);

		JButton login = new JButton("登录");
		login.addActionListener(new LoginListener());
		login.setBounds(51, 187, 97, 23);
		contentPane.add(login);

		JButton reset = new JButton("重置");
		reset.addActionListener(new ResetListener());
		reset.setBounds(180, 187, 97, 23);
		contentPane.add(reset);

		JButton regist = new JButton("注册");
		regist.addActionListener(new RegistListener());
		regist.setBounds(312, 187, 97, 23);
		contentPane.add(regist);

	}

	// 登录
	private class LoginListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			String username = name.getText();
			String password = pwd.getText();
			UserService userservice = new UserService();
			User user = userservice.findUserByName(username);
			if (user == null) {
				JOptionPane.showMessageDialog(null, "登录失败！没有找到此用户！建议先注册", "错误提示", JOptionPane.ERROR_MESSAGE);
			}
			if (user.getPassword().equals(password)) {
				JOptionPane.showMessageDialog(null, "登录成功！", "成功提示", JOptionPane.PLAIN_MESSAGE);
				MainFrame mainmenu = new MainFrame();
			} else {
				JOptionPane.showMessageDialog(null, "密码错误！", "错误提示", JOptionPane.ERROR_MESSAGE);
			}
		}
	}

	// 重置
	public class ResetListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			name.setText("");
			pwd.setText("");
		}
	}

	// 注册
	public class RegistListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			RegistFrame regist = new RegistFrame();

		}
	}

}
