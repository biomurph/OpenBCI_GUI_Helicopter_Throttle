

//////////////////////////////////////////////////////////////
//
// This class creates and manages the messaging to the Helicopter
// Any mention of Hex Bug should be considered legacy and evidence
// that Joel has not updated this class to consider the change.
// 
// 
//
// Created: Chip Audette, May-June 2014
// Modified: Joel Murphy, July 2016
//
///////////////////////////////////////////////////////////////

class Helicopter { 
 
  
  class Command {
    private String command_str;
    private String variable_str;
    private String name;
    private int counter;
    private Serial serial_h;
    public boolean printReceivedCommand = true;
//    public int ID;
    
    Command(Serial _serial_h, String _str, String _name, int _ID) {  // String _var,
      serial_h = _serial_h;
      command_str = _str;
      name =_name;
      counter = 0;
    }
    
    public void issue() {
      counter++;
      if (printReceivedCommand) {
        println("Helicopter: Command: " + name + " (" + counter + ")");
        }
        // println("A");  // verbose debug
      if (serial_h != null) serial_h.write(command_str);
        // println("B");  // verbose debug
    }
  
  } //close definition of class Command
      
  private Command command_throttle;//, // Helicopter command
                   
  private String mappedValue; // variable to control helicopter throttle
  private int counter = 0;

  //Constructor, pass in an already-opened serial port
  Helicopter(Serial serialPort) { 
    // empty
  }

  public void throttle(String V) {
      counter++;
      println("Helicopter: Command: Throttle $" +  V + " (" + counter + ")");
      helicopter_serial.write("$" + V); // shift the incoming value to ASCII
      while(helicopter_serial.available() > 0){ // hang and wait
        print(char(helicopter_serial.read()));  // for the handshake
      }

  }
  

}
