import static java.lang.System.out;

public class Endianness {

  public static int bigEndianValue (Byte[] mem) {
    boolean borrow2 = false;
    boolean borrow1 = false;
    boolean borrow0 = false;
    int mem3 = 0;
    int mem2 = 0;
    int mem1 = 0;
    int mem0 = 0;
    
    if (mem[0] >= 0){
      mem0 = mem[0];

      if (mem[1] < 0){
        mem1 = 256+mem[1];
      } else {
        mem1 = mem[1];
      }

      if (mem[2] < 0){
        mem2 = 256+mem[2];
      } else {
        mem2 = mem[2];
      }

      if (mem[3] < 0){
        mem3 = 256+mem[3];
      } else {
        mem3 = mem[3];
      }

      return mem3+256*mem2+65536*mem1+16777216*mem0;
    } else {
      if (mem[3] > 0){
        mem3 = 255 - (mem[3] - 1);
      } else if (mem[3] == 0){
        mem3 = 255;
        borrow2 = true;
      } else {
        mem3 = -mem[3];
      }

      if (borrow2){
        if (mem[2] > 0){
          mem2 = 255 - (mem[2] - 1);
        } else if (mem[2] == 0){
          mem2 = 255;
          borrow1 = true;
        } else {
          mem2 = -mem[2];
        }
      } else {
        if (mem[2] > 0){
          mem2 = 255 - mem[2];
        } else if (mem[2] == 0){
          mem2 = 255;
          borrow1 = true;
        } else {
          mem2 = -1-mem[2];
        }
      }

      if (borrow1){
        if (mem[1] > 0){
          mem1 = 255 - (mem[1] - 1);
        } else if (mem[1] == 0){
          mem1 = 255;
          borrow0 = true;
        } else {
          mem1 = -mem[1];
        }
      } else {
        if (mem[1] > 0){
          mem1 = 255 - mem[1];
        } else if (mem[1] == 0){
          mem1 = 255;
          borrow0 = true;
        } else {
          mem1 = -1-mem[1];
        }
      }

      if (borrow0){
        mem0 = -mem[0];
      } else {
        mem0 = -1-mem[0];
      }

      return -(mem3+256*mem2+65536*mem1+16777216*mem0);
    }
  }
  
  public static int littleEndianValue (Byte[] mem) {
    Byte temp = 0;

    temp = mem[3];
    mem[3] = mem[0];
    mem[0] = temp;
    temp = mem[2];
    mem[2] = mem[1];
    mem[1] = temp;

    return bigEndianValue(mem);
  }
  
  public static void main (String[] args) {
    Byte mem[] = new Byte[4];
    try {
      for (int i=0; i<4; i++)
        mem [i] = Integer.valueOf (args[i], 16) .byteValue();
    } catch (Exception e) {
      out.printf ("usage: java Endianness n0 n1 n2 n3\n");
      out.printf ("where: n0..n3 are byte values in memory at addresses 0..3 respectively, in hex (no 0x).\n");
      return;
    }
  
    int bi = bigEndianValue    (mem);
    int li = littleEndianValue (mem);
    
    out.printf ("Memory Contents\n");
    out.printf ("  Addr   Value\n");
    for (int i=0; i<4; i++)
      out.printf ("  %3d:   0x%-5x\n", i, mem[i]);
    out.printf ("The big    endian integer value at address 0 is %d\n", bi);
    out.printf ("The little endian integer value at address 0 is %d\n", li);
  }
}