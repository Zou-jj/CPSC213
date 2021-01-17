import static java.lang.System.out;

public class Endianness {

  public static int bigEndianValue (Byte[] mem) {
    if (mem[0] >= 0){
      return mem[3]+256*mem[2]+65536*mem[1]+16777216*mem[0];
    } else {
      return 0-(-mem[3])-256*(-1-mem[2])-65536*(-1-mem[1])-16777216*(255-mem[0]);
    }
  }
  
  public static int littleEndianValue (Byte[] mem) {
    if (mem[3] >= 0){
      return mem[0]+256*mem[1]+65536*mem[2]+16777216*mem[3];
    } else {
      return 0-(-mem[0])-256*(-1-mem[1])-65536*(-1-mem[2])-16777216*(255-mem[3]);
    }
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