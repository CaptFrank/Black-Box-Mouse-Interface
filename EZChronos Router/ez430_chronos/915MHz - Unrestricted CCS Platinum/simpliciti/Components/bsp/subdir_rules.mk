################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
simpliciti/Components/bsp/bsp.obj: ../simpliciti/Components/bsp/bsp.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv5/tools/compiler/msp430_4.2.1/bin/cl430" --cmd_file="Z:\Black-Box-Mouse-Interface\EZChronos Router\ez430_chronos\simpliciti\Applications\configuration\smpl_nwk_config.dat" --cmd_file="Z:\Black-Box-Mouse-Interface\EZChronos Router\ez430_chronos\simpliciti\Applications\configuration\End Device\smpl_config.dat"  -vmspx -g -O4 --opt_for_speed=0 --define=__CCE__ --define=ISM_US --define=__CC430F6137__ --define=MRFI_CC430 --include_path="C:/ti/ccsv5/ccs_base/msp430/include" --include_path="C:/ti/ccsv5/tools/compiler/msp430_4.2.1/include" --include_path="C:/ti/ccsv5/msp430/include" --include_path="Z:/Black-Box-Mouse-Interface/EZChronos Router/ez430_chronos/include" --include_path="Z:/Black-Box-Mouse-Interface/EZChronos Router/ez430_chronos/driver" --include_path="Z:/Black-Box-Mouse-Interface/EZChronos Router/ez430_chronos/logic" --include_path="Z:/Black-Box-Mouse-Interface/EZChronos Router/ez430_chronos/bluerobin" --include_path="Z:/Black-Box-Mouse-Interface/EZChronos Router/ez430_chronos/simpliciti" --include_path="Z:/Black-Box-Mouse-Interface/EZChronos Router/ez430_chronos/simpliciti/Applications/application/End Device" --include_path="Z:/Black-Box-Mouse-Interface/EZChronos Router/ez430_chronos/simpliciti/Components/bsp" --include_path="Z:/Black-Box-Mouse-Interface/EZChronos Router/ez430_chronos/simpliciti/Components/bsp/boards" --include_path="Z:/Black-Box-Mouse-Interface/EZChronos Router/ez430_chronos/simpliciti/Components/bsp/boards/CC430EM" --include_path="Z:/Black-Box-Mouse-Interface/EZChronos Router/ez430_chronos/simpliciti/Components/bsp/boards/CC430EM/bsp_external" --include_path="Z:/Black-Box-Mouse-Interface/EZChronos Router/ez430_chronos/simpliciti/Components/bsp/drivers" --include_path="Z:/Black-Box-Mouse-Interface/EZChronos Router/ez430_chronos/simpliciti/Components/bsp/drivers/code" --include_path="Z:/Black-Box-Mouse-Interface/EZChronos Router/ez430_chronos/simpliciti/Components/bsp/mcus" --include_path="Z:/Black-Box-Mouse-Interface/EZChronos Router/ez430_chronos/simpliciti/Components/mrfi" --include_path="Z:/Black-Box-Mouse-Interface/EZChronos Router/ez430_chronos/simpliciti/Components/mrfi/radios" --include_path="Z:/Black-Box-Mouse-Interface/EZChronos Router/ez430_chronos/simpliciti/Components/mrfi/radios/family5" --include_path="Z:/Black-Box-Mouse-Interface/EZChronos Router/ez430_chronos/simpliciti/Components/mrfi/smartrf" --include_path="Z:/Black-Box-Mouse-Interface/EZChronos Router/ez430_chronos/simpliciti/Components/nwk" --include_path="Z:/Black-Box-Mouse-Interface/EZChronos Router/ez430_chronos/simpliciti/Components/nwk_applications" --diag_warning=225 --call_assumptions=0 --auto_inline=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="simpliciti/Components/bsp/bsp.pp" --obj_directory="simpliciti/Components/bsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


