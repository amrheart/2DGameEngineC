import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class Main extends JFrame {
	DrawPanel canvas;
  public static void main(String[] args) {
  	new DrawTest();
    String name = "John";
    System.out.println(name);
  }
  public DrawTest(){
  	canvas = new DrawPanel();
  	this.setSize(200, 200);
    this.setVisible(true);
    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
  }
}