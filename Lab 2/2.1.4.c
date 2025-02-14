#define pinMode(ddr, port, bit, mode) do { 
    if (mode == INPUT) {                   
        ddr &= ~(1 << bit);                
        port &= ~(1 << bit);               
    } else if (mode == INPUT_PULLUP) {     
        ddr &= ~(1 << bit);               
        port |= (1 << bit);               
    } else if (mode == OUTPUT) {          
        ddr |= (1 << bit);                
    }                                     
} while(0)


