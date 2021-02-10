package arch.sm213.machine.student;

import machine.AbstractMainMemory;
import org.junit.Test;

import static org.junit.Assert.*;

public class MainMemoryTest {

    @Test
    public void testIsAccessAligned() {
        MainMemory mem = new MainMemory(8);
        assertTrue(mem.isAccessAligned(0x00000000, 4));
        assertTrue(mem.isAccessAligned(0x00000000, 8));
        assertTrue(mem.isAccessAligned(0x00000004, 4));
        assertTrue(mem.isAccessAligned(0x00000008, 4));
        assertFalse(mem.isAccessAligned(0x00000004, 8));
        assertFalse(mem.isAccessAligned(0x00000003, 4));
        assertFalse(mem.isAccessAligned(0x00000002, 4));
        assertFalse(mem.isAccessAligned(0x00000001, 4));
    }

    @Test
    public void testBytesToInteger() {
        MainMemory mem = new MainMemory(8);
        assertEquals(-2147483648, mem.bytesToInteger((byte)0x80, (byte)0x00, (byte)0x00, (byte)0x00));
        assertEquals(2147483647, mem.bytesToInteger((byte)0x7F, (byte)0xFF, (byte)0xFF, (byte)0xFF));
        assertEquals(0, mem.bytesToInteger((byte)0x00, (byte)0x00, (byte)0x00, (byte)0x00));
        assertEquals(-1, mem.bytesToInteger((byte)0xFF, (byte)0xFF, (byte)0xFF, (byte)0xFF));
        assertEquals(-255, mem.bytesToInteger((byte)0xFF, (byte)0xFF, (byte)0xFF, (byte)0x01));
        assertEquals(-65025, mem.bytesToInteger((byte)0xFF, (byte)0xFF, (byte)0x01, (byte)0xFF));
        assertEquals(-16646145, mem.bytesToInteger((byte)0xFF, (byte)0x01, (byte)0xFF, (byte)0xFF));
        assertEquals(-256, mem.bytesToInteger((byte)0xFF, (byte)0xFF, (byte)0xFF, (byte)0x00));
        assertEquals(-65280, mem.bytesToInteger((byte)0xFF, (byte)0xFF, (byte)0x01, (byte)0x00));
        assertEquals(-65535, mem.bytesToInteger((byte)0xFF, (byte)0xFF, (byte)0x00, (byte)0x01));
        assertEquals(-16711680, mem.bytesToInteger((byte)0xFF, (byte)0x01, (byte)0x00, (byte)0x00));
        assertEquals(-65536, mem.bytesToInteger((byte)0xFF, (byte)0xFF, (byte)0x00, (byte)0x00));
        assertEquals(-16711681, mem.bytesToInteger((byte)0xFF, (byte)0x00, (byte)0xFF, (byte)0xFF));
    }

    @Test
    public void testIntegerToBytes() {
        MainMemory mem = new MainMemory(8);
        assertEquals((byte)0xFF, mem.integerToBytes(-1)[0]);
        assertEquals((byte)0xFF, mem.integerToBytes(-1)[1]);
        assertEquals((byte)0xFF, mem.integerToBytes(-1)[2]);
        assertEquals((byte)0xFF, mem.integerToBytes(-1)[3]);
        assertEquals((byte)0x7F, mem.integerToBytes(2147483647)[0]);
        assertEquals((byte)0xFF, mem.integerToBytes(2147483647)[1]);
        assertEquals((byte)0xFF, mem.integerToBytes(2147483647)[2]);
        assertEquals((byte)0xFF, mem.integerToBytes(2147483647)[3]);
        assertEquals((byte)0x80, mem.integerToBytes(-2147483648)[0]);
        assertEquals((byte)0x00, mem.integerToBytes(-2147483648)[1]);
        assertEquals((byte)0x00, mem.integerToBytes(-2147483648)[2]);
        assertEquals((byte)0x00, mem.integerToBytes(-2147483648)[3]);
        assertEquals((byte)0x01, mem.integerToBytes(16909060)[0]);
        assertEquals((byte)0x02, mem.integerToBytes(16909060)[1]);
        assertEquals((byte)0x03, mem.integerToBytes(16909060)[2]);
        assertEquals((byte)0x04, mem.integerToBytes(16909060)[3]);
    }

    @Test
    public void testGet() {
        MainMemory mem = new MainMemory(8);
        try {
            mem.get(-1,4);
            fail("Exception expected");
        } catch (AbstractMainMemory.InvalidAddressException e) {
            // expected
        }
        try {
            mem.get(5,4);
            fail("Exception expected");
        } catch (AbstractMainMemory.InvalidAddressException e) {
            // expected
        }
        try {
            byte[] bytes = mem.get(0,4);
            assertEquals((byte)0x00, bytes[0]);
            assertEquals((byte)0x00, bytes[1]);
            assertEquals((byte)0x00, bytes[2]);
            assertEquals((byte)0x00, bytes[3]);
        } catch (AbstractMainMemory.InvalidAddressException e) {
            fail("Unexpected exception");
        }
        try {
            byte[] bytes = new byte[2];
            bytes[0] = (byte) 0xAB;
            bytes[1] = (byte) 0x12;
            mem.set(0, bytes);
            assertEquals((byte)0xAB, mem.get(0,4)[0]);
            assertEquals((byte)0x12, mem.get(0,4)[1]);
        } catch (AbstractMainMemory.InvalidAddressException e) {
            fail("Unexpected exception");
        }
    }

    @Test
    public void testSet() {
        MainMemory mem = new MainMemory(8);
        assertEquals(8, mem.length());
        try {
            byte[] bytes = new byte[4];
            mem.set(-1,bytes);
            fail("Exception expected");
        } catch (AbstractMainMemory.InvalidAddressException e) {
            // expected
        }
        try {
            byte[] bytes = new byte[4];
            mem.set(5,bytes);
            fail("Exception expected");
        } catch (AbstractMainMemory.InvalidAddressException e) {
            // expected
        }
        try {
            byte[] bytes = new byte[4];
            bytes[0] = (byte) 0xAB;
            bytes[1] = (byte) 0x12;
            bytes[2] = (byte) 0x34;
            bytes[3] = (byte) 0xCD;
            mem.set(0, bytes);
            assertEquals((byte)0xAB, mem.get(0,4)[0]);
            assertEquals((byte)0x12, mem.get(0,4)[1]);
            assertEquals((byte)0xAB, mem.get(0,4)[0]);
            assertEquals((byte)0x12, mem.get(0,4)[1]);
        } catch (AbstractMainMemory.InvalidAddressException e) {
            fail("Unexpected exception");
        }
    }
}