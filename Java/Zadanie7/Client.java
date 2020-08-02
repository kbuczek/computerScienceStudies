import java.awt.Font;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.GridBagLayout;
import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Scanner;
import java.io.PrintWriter;
import java.net.Socket;
import javax.swing.*;

public class Client {

    private JFrame frame = new JFrame("Kolko i krzyzyk");
    private JLabel messageLabel = new JLabel("...");

    private Square[] board = new Square[9];
    private Square currentSquare;

    private Socket socket;
    private Scanner in;
    private PrintWriter out;

    public Client(String serverAddress) throws Exception {

        socket = new Socket(serverAddress, 58901);
        in = new Scanner(socket.getInputStream());
        out = new PrintWriter(socket.getOutputStream(), true);


        messageLabel.setBackground(Color.lightGray);
        frame.getContentPane().add(messageLabel, BorderLayout.SOUTH);

        JPanel boardPanel = new JPanel();
        boardPanel.setBackground(Color.black);
        boardPanel.setLayout(new GridLayout(3, 3, 2, 2));
        for (int i = 0; i < board.length; i++) {
            final int j = i;
            board[i] = new Square();
            board[i].addMouseListener(new MouseAdapter() {
                public void mousePressed(MouseEvent e) {
                    currentSquare = board[j];
                    out.println("MOVE " + j);
                }
            });
            boardPanel.add(board[i]);
        }
        frame.getContentPane().add(boardPanel, BorderLayout.CENTER);

        //menu
        JMenuBar jmb = new JMenuBar();
        frame.setJMenuBar(jmb);

        JMenu opcje = new JMenu("Opcje");
        jmb.add(opcje);

        JMenuItem zapisz = new JMenuItem(new AbstractAction("Zapisz gre"){
            public void actionPerformed(ActionEvent e) {
                messageLabel.setText("Zapisuje stan gry.");
                out.println("SAVE");
                refresh();
            }
        });
        opcje.add(zapisz);

        JMenuItem wczytaj = new JMenuItem(new AbstractAction("Wczytaj ostatnia gre"){
            public void actionPerformed(ActionEvent e) {
                messageLabel.setText("Wczytano ostatnia gre.");
                out.println("OPEN");
                refresh();
                out.println("REFRESH_OPPONENT");
            }
        });
        opcje.add(wczytaj);
    }

    public void refresh() {
        for(int i = 0; i < board.length; i++) {
            out.println("CHECK " + i);
        }
    }

    public void play() throws Exception {
        try {
            String response = in.nextLine();
            char mark = response.charAt(8);
            char opponentMark = mark == 'X' ? 'O' : 'X';
            frame.setTitle("Kolko i krzyzyk: Gracz " + mark);
            while (in.hasNextLine()) {
                response = in.nextLine();
                if (response.startsWith("VALID_MOVE")) {
                    messageLabel.setText("Przeslano ruch, czekaj.");
                    currentSquare.setText(mark);
                    currentSquare.repaint();
                } else if (response.startsWith("OPPONENT_MOVED")) {
                    int loc = Integer.parseInt(response.substring(15));
                    board[loc].setText(opponentMark);
                    board[loc].repaint();
                    messageLabel.setText("Przeciwnik sie ruszyl, twoj ruch");
                } else if (response.startsWith("MESSAGE")) {
                    messageLabel.setText(response.substring(8));
                } else if (response.startsWith("VICTORY")) {
                    JOptionPane.showMessageDialog(frame, "Wygrales");
                    break;
                } else if (response.startsWith("DEFEAT")) {
                    JOptionPane.showMessageDialog(frame, "Przegrales");
                    break;
                } else if (response.startsWith("TIE")) {
                    JOptionPane.showMessageDialog(frame, "Remis");
                    break;
                } else if (response.startsWith("OTHER_PLAYER_LEFT")) {
                    JOptionPane.showMessageDialog(frame, "Przeciwnik wyszedl");
                    break;
                } else if (response.startsWith("X")) {
                    int loc = Integer.parseInt(response.substring(2));
                    board[loc].setText('X');
                    board[loc].repaint();
                } else if (response.startsWith("O")) {
                    int loc = Integer.parseInt(response.substring(2));
                    board[loc].setText('O');
                    board[loc].repaint();
                } else if (response.startsWith("NULL")) {
                    int loc = Integer.parseInt(response.substring(5));
                    board[loc].setText(' ');
                    board[loc].repaint();
                } else if (response.startsWith("REFRESH")) {
                    refresh();
                }
            }
            out.println("QUIT");
        } catch (Exception e) {
            e.printStackTrace();
        }
        finally {
            socket.close();
            frame.dispose();
        }
    }

    static class Square extends JPanel {
        JLabel label = new JLabel();

        public Square() {
            setBackground(Color.lightGray);
            setLayout(new GridBagLayout());
            label.setFont(new Font("Arial", Font.BOLD, 60));
            add(label);
        }

        public void setText(char text) {
            label.setForeground(text == 'X' ? Color.BLUE : Color.RED);
            label.setText(text + "");
        }
    }

    public static void main(String[] args) throws Exception {
        if (args.length != 1) {
            System.err.println("Podaj numer IP (local: 127.0.0.1)");
            return;
        }
        Client client = new Client(args[0]);
        client.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        client.frame.setSize(320, 320);
        client.frame.setVisible(true);
        client.frame.setResizable(true);
        client.play();
    }
}