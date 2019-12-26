/*         
         Contiguous SARAM memory blocks can be combined 
         if required to create a larger memory block. 
*/


MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to SARAM" bootloader mode      */
   /* BOOT_RSVD is used by the boot ROM for stack.               */
   /* This section is only reserved to keep the BOOT ROM from    */
   /* corrupting this area during the debug process              */
   
   BEGIN      : origin = 0x000000, length = 0x000002     /* Boot to M0 will go here                      */
   BOOT_RSVD  : origin = 0x000002, length = 0x00004E     /* Part of M0, BOOT rom will use this for stack */               
   RAMM0      : origin = 0x000050, length = 0x0003B0
/*
   RAML0      : origin = 0x008000, length = 0x001000    
   RAML1      : origin = 0x009000, length = 0x001000    
   RAML2      : origin = 0x00A000, length = 0x001000    
   RAML3      : origin = 0x00B000, length = 0x001000 
*/
   RAML       : origin = 0x008000, length = 0x004000
   ZONE7A     : origin = 0x200000, length = 0x00FC00    /* XINTF zone 7 - program space */ 
   CSM_RSVD   : origin = 0x33FF80, length = 0x000076     /* Part of FLASHA.  Program with all 0x0000 when CSM is in use. */
   CSM_PWL    : origin = 0x33FFF8, length = 0x000008     /* Part of FLASHA.  CSM password locations in FLASHA            */
   ADC_CAL    : origin = 0x380080, length = 0x000009
   RESET      : origin = 0x3FFFC0, length = 0x000002
   IQTABLES   : origin = 0x3FE000, length = 0x000b50
   IQTABLES2  : origin = 0x3FEB50, length = 0x00008c
   FPUTABLES  : origin = 0x3FEBDC, length = 0x0006A0
   BOOTROM    : origin = 0x3FF27C, length = 0x000D44               

         
PAGE 1 : 
   RAMM       : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
/*
   RAML4      : origin = 0x00C000, length = 0x001000    
   RAML5      : origin = 0x00D000, length = 0x001000    
   RAML6      : origin = 0x00E000, length = 0x001000    
   RAML7      : origin = 0x00F000, length = 0x001000 
*/
   RAMH       : origin = 0x00C000, length = 0x004000
   ZONE7B     : origin = 0x20FC00, length = 0x000400     /* XINTF zone 7 - data space */
}
 
 
SECTIONS
{
   /* Setup for "boot to SARAM" mode: 
      The codestart section (found in DSP28_CodeStartBranch.asm)
      re-directs execution to the start of user code.  */
   codestart        : > BEGIN,     PAGE = 0
   ramfuncs         : > RAML,      PAGE = 0  
   .text            : > RAML,      PAGE = 0
   .cinit           : > RAML,      PAGE = 0
   .pinit           : > RAML,      PAGE = 0
   .switch          : > RAML,      PAGE = 0
   
   .stack           : > RAMM,      PAGE = 1
   .ebss            : > RAMH,      PAGE = 1
   .econst          : > RAMH,      PAGE = 1      
   .esysmem         : > RAMM,      PAGE = 1

   IQmath           : > RAML,      PAGE = 0
   IQmathTables     : > IQTABLES,  PAGE = 0, TYPE = NOLOAD 
   IQmathTables2    : > IQTABLES2, PAGE = 0, TYPE = NOLOAD 
   FPUmathTables    : > FPUTABLES, PAGE = 0, TYPE = NOLOAD 
/*      
   DMARAML4         : > RAML4,     PAGE = 1
   DMARAML5         : > RAML5,     PAGE = 1
   DMARAML6         : > RAML6,     PAGE = 1
   DMARAML7         : > RAML7,     PAGE = 1
*/   
   ZONE7DATA        : > ZONE7B,    PAGE = 1  

   .reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used                    */
   csm_rsvd         : > CSM_RSVD   PAGE = 0, TYPE = DSECT /* not used for SARAM examples */
   csmpasswds       : > CSM_PWL    PAGE = 0, TYPE = DSECT /* not used for SARAM examples */
   
   /* Allocate ADC_cal function (pre-programmed by factory into TI reserved memory) */
   .adc_cal     : load = ADC_CAL,   PAGE = 0, TYPE = NOLOAD
     
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
