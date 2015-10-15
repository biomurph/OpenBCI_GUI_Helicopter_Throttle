

//////////////////////////////////////////////////////////////
//
// This class creates and manages the messaging to the Hex Bug
//
// Created: Chip Audette, May-June 2014
//
///////////////////////////////////////////////////////////////

class HexBug {  // change to helicopter
      
   private int wait_millis = 5;
   private boolean fireBetweenMoves = false;
  
  //create inner class to wrap up a "command"
  class Command {
    private String command_str;
    private String variable_str;
    private String name;
//    private String mappedValue; // variable to control throttle
    private int counter;
    private Serial serial_h;
    public boolean printReceivedCommand = true;
    public int ID;
    
    Command(Serial _serial_h, String _str, String _var, String _name, int _ID) {
      serial_h = _serial_h;
      command_str = _str;
      variable_str = _var;
      name =_name;
      counter = 0;
      ID = _ID;
    }
    
    public int issue() {
      counter++;
      if (printReceivedCommand) {
        println("HexBug: Command: " + name + " (" + counter + ")");
      }
      if (serial_h != null) serial_h.write(command_str);
      return ID;
    }
  
  } //close definition of class Command
    
  private Command command_forward, command_climb, command_dive, command_left, command_right,
                  command_throttle; 
  private int prev_command = -1;
  private String mappedValue; // variable to control throttle
  private int counter = 0;
  //Constructor, pass in an already-opened serial port
  HexBug(Serial serialPort) {
    int ID = 0;//  display comands
   command_forward = new Command(serialPort,"O","Swim!",ID++);
   command_right = new Command(serialPort,"|","Right",ID++);
   command_left = new Command(serialPort,"{","Left",ID++);
   command_climb = new Command(serialPort,"}","Climb",ID++);
   command_dive = new Command(serialPort,"P","Dive",ID++);
     
  }
  
  public void climb() {
    prev_command = command_climb.issue();
  }
  public void dive() {
    prev_command = command_dive.issue();
  }
  public void forward() {
    //if (fireBetweenMoves & (prev_command != command_forward.ID)) {
     prev_command = command_fire.issue();  //issue a FIRE command on a transition
     waitMilliseconds(wait_millis);
    //}
    prev_command = command_forward.issue();
  }
  public void left() {
    //if (fireBetweenMoves & (prev_command != command_left.ID)) {
     prev_command = command_fire.issue();  //issue a FIRE command on a transition
     waitMilliseconds(wait_millis);
    //}
    prev_command = command_left.issue();
  }
  public void right() {
    //if (fireBetweenMoves & (prev_command != command_right.ID)) {
     prev_command = command_fire.issue();  //issue a FIRE command on a transition
     waitMilliseconds(wait_millis);
    //}
    prev_command = command_right.issue();
  }

  public void throttle(String V) {
      counter++;
      println("HexBug: Command: Throttle $" +  V + " (" + counter + ")");
      hexBug_serial.write("$" + V);
      while(hexBug_serial.available() > 0){
        print(char(hexBug_serial.read()));
      }

  }
  
  public void waitMilliseconds(int dt_millis) {
      int start_time = millis();
      int t = millis();
      while (t-start_time < dt_millis) {
        t = millis();
      }
  }

}
