package arch.sm213.machine.student;

import machine.AbstractMainMemory;


/**
 * Main Memory of Simple CPU.
 * <p>
 * Provides an abstraction of main memory (DRAM).
 */

public class MainMemory extends AbstractMainMemory {
    private byte[] mem;

    /**
     * Allocate memory.
     *
     * @param byteCapacity size of memory in bytes.
     */
    public MainMemory(int byteCapacity) {
        mem = new byte[byteCapacity];
    }

    /**
     * Determine whether an address is aligned to specified length.
     *
     * @param address memory address.
     * @param length  byte length.
     * @return true iff address is aligned to length.
     */
    @Override
    protected boolean isAccessAligned(int address, int length) {
        return address % length == 0;
    }

    /**
     * Convert an sequence of four bytes into a Big Endian integer.
     *
     * @param byteAtAddrPlus0 value of byte with lowest memory address (base address).
     * @param byteAtAddrPlus1 value of byte at base address plus 1.
     * @param byteAtAddrPlus2 value of byte at base address plus 2.
     * @param byteAtAddrPlus3 value of byte at base address plus 3 (highest memory address).
     * @return Big Endian integer formed by these four bytes.
     */
    @Override
    public int bytesToInteger(byte byteAtAddrPlus0, byte byteAtAddrPlus1, byte byteAtAddrPlus2, byte byteAtAddrPlus3) {

        boolean borrow2 = false;
        boolean borrow1 = false;
        boolean borrow0 = false;
        int mem3 = 0;
        int mem2 = 0;
        int mem1 = 0;
        int mem0 = 0;

        if (byteAtAddrPlus0 >= 0) {
            mem0 = byteAtAddrPlus0;

            if (byteAtAddrPlus1 < 0) {
                mem1 = 256 + byteAtAddrPlus1;
            } else {
                mem1 = byteAtAddrPlus1;
            }

            if (byteAtAddrPlus2 < 0) {
                mem2 = 256 + byteAtAddrPlus2;
            } else {
                mem2 = byteAtAddrPlus2;
            }

            if (byteAtAddrPlus3 < 0) {
                mem3 = 256 + byteAtAddrPlus3;
            } else {
                mem3 = byteAtAddrPlus3;
            }

            return mem3 + 256 * mem2 + 65536 * mem1 + 16777216 * mem0;
        } else {
            if (byteAtAddrPlus3 > 0) {
                mem3 = 255 - (byteAtAddrPlus3 - 1);
            } else if (byteAtAddrPlus3 == 0) {
                mem3 = 0;
                borrow2 = true;
            } else {
                mem3 = -byteAtAddrPlus3;
            }

            if (borrow2) {
                if (byteAtAddrPlus2 > 0) {
                    mem2 = 255 - (byteAtAddrPlus2 - 1);
                } else if (byteAtAddrPlus2 == 0) {
                    mem2 = 0;
                    borrow1 = true;
                } else {
                    mem2 = -byteAtAddrPlus2;
                }
            } else {
                if (byteAtAddrPlus2 > 0) {
                    mem2 = 255 - byteAtAddrPlus2;
                } else if (byteAtAddrPlus2 == 0) {
                    mem2 = 255;
                } else {
                    mem2 = -1 - byteAtAddrPlus2;
                }
            }

            if (borrow1) {
                if (byteAtAddrPlus1 > 0) {
                    mem1 = 255 - (byteAtAddrPlus1 - 1);
                } else if (byteAtAddrPlus1 == 0) {
                    mem1 = 0;
                    borrow0 = true;
                } else {
                    mem1 = -byteAtAddrPlus1;
                }
            } else {
                if (byteAtAddrPlus1 > 0) {
                    mem1 = 255 - byteAtAddrPlus1;
                } else if (byteAtAddrPlus1 == 0) {
                    mem1 = 255;
                } else {
                    mem1 = -1 - byteAtAddrPlus1;
                }
            }

            if (borrow0) {
                mem0 = -byteAtAddrPlus0;
            } else {
                mem0 = -1 - byteAtAddrPlus0;
            }

            return -(mem3 + 256 * mem2 + 65536 * mem1 + 16777216 * mem0);
        }
    }

    /**
     * Convert a Big Endian integer into an array of 4 bytes organized by memory address.
     *
     * @param i an Big Endian integer.
     * @return an array of byte where [0] is value of low-address byte of the number etc.
     */
    @Override
    public byte[] integerToBytes(int i) {

        int low;
        int high;
        long result;
        byte[] bytes = new byte[4];

        if (i >= 0) {
            result = i;
        } else {
            result = i;
            result += 2147483647;
            result += 1;
            result += 2147483647;
            result += 1;
        }

        for (int index = 3; index >= 0; index--) {
            low = (int) (result % 16);
            result /= 16;
            high = (int) (result % 16);
            result /= 16;
            bytes[index] = (byte) (low + 16 * high);
        }
        return bytes;
    }

    /**
     * Fetch a sequence of bytes from memory.
     *
     * @param address address of the first byte to fetch.
     * @param length  number of bytes to fetch.
     * @return an array of byte where [0] is memory value at address, [1] is memory value at address+1 etc.
     * @throws InvalidAddressException if any address in the range address to address+length-1 is invalid.
     */
    @Override
    protected byte[] get(int address, int length) throws InvalidAddressException {
        byte[] bytes = new byte[length];
        if (address + length - 1 >= mem.length || address < 0) {
            throw new InvalidAddressException();
        }
        for (int index = 0; index < length; index++) {
            bytes[index] = mem[address + index];
        }
        return bytes;
    }

    /**
     * Store a sequence of bytes into memory.
     *
     * @param address address of the first byte in memory to recieve the specified value.
     * @param value   an array of byte values to store in memory at the specified address.
     * @throws InvalidAddressException if any address in the range address to address+value.length-1 is invalid.
     */
    @Override
    protected void set(int address, byte[] value) throws InvalidAddressException {
        if (address + value.length - 1 >= mem.length || address < 0) {
            throw new InvalidAddressException();
        }
        for (int index = 0; index < value.length; index++) {
            mem[address + index] = value[index];
        }
    }

    /**
     * Determine the size of memory.
     *
     * @return the number of bytes allocated to this memory.
     */
    @Override
    public int length() {
        return mem.length;
    }
}
