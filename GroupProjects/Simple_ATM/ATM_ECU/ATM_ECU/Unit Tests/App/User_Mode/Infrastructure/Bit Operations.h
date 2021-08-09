#ifndef __BIT_OPERATIONS_H__
	#define __BIT_OPERATIONS_H__	
	
	#define Bit(x) (1<<(x))
	
	#define SET_BIT(REG, BIT)     ((REG) |=   (Bit(BIT)))
	
	#define CLEAR_BIT(REG, BIT)   ((REG) &=  ~(Bit(BIT)))
	
	#define READ_BIT(REG, BIT)    (((REG) &   (Bit(BIT))) >> (BIT))
	
	#define TOG_BIT(REG,BIT) 	  ((REG) ^=   (Bit(BIT)))

	#define CLEAR_REG(REG)        ((REG)  =   (Bit(BIT)))
	
	#define TOG_BIT(REG,BIT)      ((REG) ^=   (Bit(BIT)))

	#define WRITE_REG(REG, VAL)   ((REG)  =   (VAL))

	#define TOG_REG(REG,VAL) 	  ((REG) ^=   (VAL))
	
	#define READ_REG(REG)         ((REG))
	
	#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))
		
#endif
