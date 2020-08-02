import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import java.io.File;
import javax.xml.bind.*;
import javax.xml.bind.annotation.*;

public class Server {

    public static void main(String[] args) throws Exception {
        try (ServerSocket listener = new ServerSocket(58901)) {
            System.out.println("Serwer kolko i krzyzyk jest uruchomiony...");
            ExecutorService pool = Executors.newFixedThreadPool(200);
            try {
                while (true) {
                    Game game = new Game();
                    pool.execute(game.new Player(listener.accept(), 'X'));
                    pool.execute(game.new Player(listener.accept(), 'O'));
                }
            } finally {
                listener.close();
            }
        }
    }

}

@XmlRootElement(name = "board")
class Board  {
    char place0, place1, place2, place3, place4, place5, place6, place7, place8;

    @XmlElement(name = "place0")
    public void setBoard0(char place) {
        this.place0 = place;
    }
    @XmlElement(name = "place1")
    public void setBoard1(char place) {
        this.place1 = place;
    }
    @XmlElement(name = "place2")
    public void setBoard2(char place) {
        this.place2 = place;
    }
    @XmlElement(name = "place3")
    public void setBoard3(char place) {
        this.place3 = place;
    }
    @XmlElement(name = "place4")
    public void setBoard4(char place) {
        this.place4 = place;
    }
    @XmlElement(name = "place5")
    public void setBoard5(char place) {
        this.place5 = place;
    }
    @XmlElement(name = "place6")
    public void setBoard6(char place) {
        this.place6 = place;
    }
    @XmlElement(name = "place7")
    public void setBoard7(char place) {
        this.place7 = place;
    }
    @XmlElement(name = "place8")
    public void setBoard8(char place) {
        this.place8 = place;
    }

    public char getBoard0() {
        return place0;
    }
    public char getBoard1() {
        return place1;
    }
    public char getBoard2() {
        return place2;
    }
    public char getBoard3() {
        return place3;
    }
    public char getBoard4() {
        return place4;
    }
    public char getBoard5() {
        return place5;
    }
    public char getBoard6() {
        return place6;
    }
    public char getBoard7() {
        return place7;
    }
    public char getBoard8() {
        return place8;
    }

    @Override
    public String toString() {
        return getBoard0() + "|" + getBoard1() + "|" + getBoard2() + "\n" +
                getBoard3() + "|" + getBoard4() + "|" + getBoard5() + "\n" +
                getBoard6() + "|" + getBoard7() + "|" + getBoard8();
    }
}

class Game {
    public char[] board = new char[9];

    Player currentPlayer;
    Player savedCurrentPlayer;

    public boolean hasWinner() {
        return (board[0] != '\0' && board[0] == board[1] && board[0] == board[2])
                || (board[3] != '\0' && board[3] == board[4] && board[3] == board[5])
                || (board[6] != '\0' && board[6] == board[7] && board[6] == board[8])
                || (board[0] != '\0' && board[0] == board[3] && board[0] == board[6])
                || (board[1] != '\0' && board[1] == board[4] && board[1] == board[7])
                || (board[2] != '\0' && board[2] == board[5] && board[2] == board[8])
                || (board[0] != '\0' && board[0] == board[4] && board[0] == board[8])
                || (board[2] != '\0' && board[2] == board[4] && board[2] == board[6]);
    }

    public boolean boardFilledUp() {
        for (int i = 0; i < 9; i++) {
            if (board[i] == '\0') {
                return false;
            }
        }
        return true;
    }

    public synchronized void move(int location, Player player) {
        if (player != currentPlayer) {
            throw new IllegalStateException("Poczekaj na swoja kolej");
        } else if (player.opponent == null) {
            throw new IllegalStateException("Czekam na przeciwnika");
        } else if (board[location] != '\0') {
            throw new IllegalStateException("Miejsce jest juz zajete");
        }
        board[location] = currentPlayer.mark;
        //board.setBoard(location, currentPlayer.mark);
        currentPlayer = currentPlayer.opponent;
    }

    public synchronized void save() {
        System.out.println("zapisuje stan gry");

        savedCurrentPlayer = currentPlayer;

        Board savedBoard = new Board();
        savedBoard.setBoard0(board[0]);
        savedBoard.setBoard1(board[1]);
        savedBoard.setBoard2(board[2]);
        savedBoard.setBoard3(board[3]);
        savedBoard.setBoard4(board[4]);
        savedBoard.setBoard5(board[5]);
        savedBoard.setBoard6(board[6]);
        savedBoard.setBoard7(board[7]);
        savedBoard.setBoard8(board[8]);

        try {
            File file = new File("zapis.xml");
            JAXBContext jaxbContext = JAXBContext.newInstance(Board.class);
            Marshaller jaxbMarshaller = jaxbContext.createMarshaller();

            // output pretty printed
            jaxbMarshaller.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);

            jaxbMarshaller.marshal(savedBoard, System.out);
            jaxbMarshaller.marshal(savedBoard, file);
        } catch (JAXBException e) {
            e.printStackTrace();
        }
    }

    public synchronized void open() {
        System.out.println("wczytuje ostatnia gre");
        try {
            File xmlFile = new File("zapis.xml");
            JAXBContext jaxbContext = JAXBContext.newInstance(Board.class);

            Unmarshaller jaxbUnmarshaller = jaxbContext.createUnmarshaller();
            Board openedBoard = (Board) jaxbUnmarshaller.unmarshal(xmlFile);
            System.out.println(openedBoard);

            board[0] = openedBoard.getBoard0();
            board[1] = openedBoard.getBoard1();
            board[2] = openedBoard.getBoard2();
            board[3] = openedBoard.getBoard3();
            board[4] = openedBoard.getBoard4();
            board[5] = openedBoard.getBoard5();
            board[6] = openedBoard.getBoard6();
            board[7] = openedBoard.getBoard7();
            board[8] = openedBoard.getBoard8();

            currentPlayer = savedCurrentPlayer;

        } catch (JAXBException e) {
            e.printStackTrace();
        }
    }

    class Player extends Thread {
        char mark;
        Player opponent;
        Socket socket;
        Scanner input;
        PrintWriter output;

        public Player(Socket socket, char mark) {
            this.socket = socket;
            this.mark = mark;
        }

        public void setOpponent(Player opponent) {
            this.opponent = opponent;
        }

        public void run() {
            try {
                setup();
                processCommands();
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                if (opponent != null && opponent.output != null) {
                    opponent.output.println("OTHER_PLAYER_LEFT");
                }
                try {
                    socket.close();
                } catch (IOException e) {
                }
            }
        }

        private void setup() throws IOException {
            input = new Scanner(socket.getInputStream());
            output = new PrintWriter(socket.getOutputStream(), true);
            output.println("WELCOME " + mark);
            if (mark == 'X') {
                currentPlayer = this;
                output.println("MESSAGE Czekam na przeciwnika");
            } else {
                opponent = currentPlayer;
                opponent.opponent = this;
                opponent.output.println("MESSAGE Twoj ruch");
            }
        }

        private void processCommands() {
            while (input.hasNextLine()) {
                String command = input.nextLine();
                if (command.startsWith("QUIT")) {
                    return;
                } else if (command.startsWith("MOVE")) {
                    processMoveCommand(Integer.parseInt(command.substring(5)));
                } else if (command.startsWith("SAVE")) {
                    save();
                } else if (command.startsWith("OPEN")) {
                    open();
                } else if (command.startsWith("CHECK")) {
                    checkCommand(Integer.parseInt(command.substring(6)));
                } else if (command.startsWith("REFRESH_OPPONENT")) {
                    opponent.output.println("REFRESH");
                }
            }
        }

        private void processMoveCommand(int location) {
            try {
                move(location, this);
                output.println("VALID_MOVE");
                opponent.output.println("OPPONENT_MOVED " + location);
                if (hasWinner()) {
                    output.println("VICTORY");
                    opponent.output.println("DEFEAT");
                } else if (boardFilledUp()) {
                    output.println("TIE");
                    opponent.output.println("TIE");
                }
            } catch (IllegalStateException e) {
                output.println("MESSAGE " + e.getMessage());
            }
        }

        public void checkCommand(int location) {
            if(board[location] == 'X') {
                output.println("X " + location);
            } else if (board[location] == 'O') {
                output.println("O " + location);
            } else if (board[location] == '\0') {
                output.println("NULL " + location);
            }
        }
    }
}



