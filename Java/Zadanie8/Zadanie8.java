import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Statement;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;


public class Zadanie8  extends JFrame{

	public static Connection connect() {
		 try {
			 Class.forName("org.hsqldb.jdbc.JDBCDriver");
		 } catch (Exception e) {
		     System.err.println("ERROR: failed to load HSQLDB JDBC driver.");
		     e.printStackTrace();
		     return null;
		 }
		 Connection c = null;
		 try {
			 c = DriverManager.getConnection("jdbc:hsqldb:file:testdb", "SA", "");
		 } catch(SQLException e) {
			 System.err.println("ERROR: cannot connect to database db.");
			 e.printStackTrace();
		 }
		 return c;		 
	}

	//funkcja dodaj
	public void addValue(Connection c) {
			JFrame frame = new JFrame("Dodaj kontakt");
			JPanel panel = new JPanel();
			frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

			JLabel textLabel = new JLabel("Wprowadź imię:");
			JTextField textImie = new JTextField(10);
			JLabel textLabel2 = new JLabel("Wprowadź numer:");
			JTextField textNumer = new JTextField(9);


			JButton submit = new JButton("Dodaj");
			submit.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					String wpiszNumer = "";
					String wpiszImie = "";
					int wpiszNumerInt = 0;
					wpiszImie = textImie.getText();
					wpiszNumer = textNumer.getText();
					System.out.println(wpiszImie);
					System.out.println(wpiszNumer);
					try {
						wpiszNumerInt = Integer.parseInt(wpiszNumer);
					} catch (NumberFormatException ex) {
						ex.printStackTrace();
					}
					try {
						Statement stmt = c.createStatement();
						stmt.executeUpdate("INSERT INTO KSIAZKA(NUMER, IMIE) VALUES ("+wpiszNumerInt+", '"+wpiszImie+"');");
					} catch (SQLException ex) {
						ex.printStackTrace();
					}
					printDataBase(c);
				}
			});
			panel.add(textLabel);
			panel.add(textImie);
			panel.add(textLabel2);
			panel.add(textNumer);
			panel.add(submit);
			frame.setLocationRelativeTo(null);
			frame.add(panel);
			frame.setSize(250, 200);
			frame.setVisible(true);
	}

	//funkcja usun
	public void deleteValue(Connection c) {
			JFrame frame = new JFrame("Usuń kontakt");
			JPanel panel = new JPanel();
			frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

			JLabel textLabel = new JLabel("Wprowadź imię:");
			JTextField textImie = new JTextField(10);

			JButton delete = new JButton("Usuń");
			delete.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					String wpiszImie = "";
					wpiszImie = textImie.getText();
					System.out.println(wpiszImie);
					try {
						Statement stmt = c.createStatement();
						stmt.executeUpdate("DELETE FROM ksiazka WHERE imie ='"+wpiszImie+"'");
					} catch (SQLException ex) {
						ex.printStackTrace();
					}
					printDataBase(c);
				}
			});

			panel.add(textLabel);
			panel.add(textImie);
			panel.add(delete);
			frame.setLocationRelativeTo(null);
			frame.add(panel);
			frame.setSize(250, 200);
			frame.setVisible(true);
	}

	//funkcja wyszukaj i zmien
	public void searchValue(Connection c){
			JFrame frame = new JFrame("Wyszukaj i zmień kontakt");
			JPanel panel = new JPanel();
			frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

			JLabel textLabel = new JLabel("Wprowadź imię szukanej osoby:");
			JTextField textImie = new JTextField(10);
			JLabel textLabel2 = new JLabel("Wprowadź nowy numer:");
			JTextField textNumer = new JTextField(9);

			JButton submit = new JButton("Zmień");
			submit.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					String wpiszNumer = "";
					String wpiszImie = "";
					int wpiszNumerInt = 0;
					wpiszImie = textImie.getText();
					wpiszNumer = textNumer.getText();
					System.out.println(wpiszImie);
					System.out.println(wpiszNumer);
					try {
						wpiszNumerInt = Integer.parseInt(wpiszNumer);
					} catch (NumberFormatException ex) {
						ex.printStackTrace();
					}
					try {
						Statement stmt = c.createStatement();
						stmt.executeUpdate("UPDATE ksiazka SET numer = "+wpiszNumerInt+"  WHERE imie='"+wpiszImie+"'");
					} catch (SQLException ex) {
						ex.printStackTrace();
					}
					printDataBase(c);
				}
			});
			panel.add(textLabel);
			panel.add(textImie);
			panel.add(textLabel2);
			panel.add(textNumer);
			panel.add(submit);
			frame.setLocationRelativeTo(null);
			frame.add(panel);
			frame.setSize(250, 200);
			frame.setVisible(true);
	}

	public static void printDataBase(Connection c) {
		try {
			Statement stmt = c.createStatement();
			ResultSet rs = stmt.executeQuery("SELECT * FROM ksiazka");
			JFrame frameDB = new JFrame("Baza Danych ");
			JPanel panel = new JPanel();
			frameDB.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
			panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
			JLabel print2 = new JLabel("NUMER" + "        " + "IMIE");
			panel.add(print2);

			while(rs.next()) {
				String dbrow = rs.getInt("numer") + ", " + rs.getString("imie");
				JLabel print = new JLabel(dbrow);
				panel.add(print);
			}

			frameDB.setLocationRelativeTo(null);
			frameDB.add(panel);
			frameDB.setSize(250, 500);
			frameDB.setVisible(true);
		} catch (SQLException e) {
			e.printStackTrace();
		}

	}

//	tworzenie bazy danych (potrzebne tylko raz)
//	public static void createTable(Connection c) throws SQLException {
//		Statement stmt = c.createStatement();
//		stmt.executeUpdate("CREATE TABLE ksiazka(numer INTEGER1, imie VARCHAR(64));");
//	}
//
//	public static void fillTableWithData(Connection c) throws SQLException {
//		Statement stmt = c.createStatement();
//		stmt.executeUpdate("INSERT INTO ksiazka(numer, imie) VALUES (111222333, 'Czarek');");
//	}
//
//	public static void initDB(Connection c) throws SQLException{
//		createTable(c); //baze danych mozna tworzyc tylko raz
//		fillTableWithData(c); //wypelnic mozna ja ile razy chcemy
//	}
	
	public static void main(String[] args) {
		Connection c = connect();
		//tworzenie bazy danych
		/*try {
			initDB(c);
		} catch (SQLException ex) {
			System.err.println("Problem with creating table.");
			ex.printStackTrace();
			try {
				c.close();
			} catch(SQLException e) {
				e.printStackTrace();
			}
			return;
		}*/
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		Zadanie8 p = new Zadanie8();
        JFrame frame = new JFrame("Menu");
        JPanel panel = new JPanel();
        frame.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));

		JButton addValueButton = new JButton("Dodaj kontakt");
		addValueButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				p.addValue(c);
			}
		});
		panel.add(addValueButton);

		JButton deleteValueButton = new JButton("Usuń kontakt");
		deleteValueButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				p.deleteValue(c);
			}
		});
		panel.add(deleteValueButton);

		JButton searchValueButton = new JButton("Wyszukaj i zmień kontakt");
		searchValueButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				p.searchValue(c);
			}
		});
		panel.add(searchValueButton);

		JButton printButton = new JButton("Pokaż bazę danych");
		printButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				printDataBase(c);
			}
		});
		panel.add(printButton);

		JButton exitButton = new JButton("Wyjdź");
		exitButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				try {
					Statement stmt = c.createStatement();
					stmt.execute("SHUTDOWN;");
					c.close();
					System.exit(0);
				} catch (SQLException ex) {
					ex.printStackTrace();
				}

			}
		});
		panel.add(exitButton);

		frame.setLocationRelativeTo(null);
		frame.add(panel);
		frame.setSize(250, 200);
		frame.setVisible(true);
	}
}
