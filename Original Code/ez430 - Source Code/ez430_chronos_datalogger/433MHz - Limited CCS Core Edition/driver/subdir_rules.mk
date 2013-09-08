################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
driver/ports.obj: ../driver/ports.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/mnt/ccsv5/tools/compiler/msp430_4.1.5/bin/cl430" -vmspx -g -O4 --opt_for_speed=0 --define=__CCE__ --define=ISM_LF --include_path="/mnt/ccsv5/ccs_base/msp430/include" --include_path="/mnt/ccsv5/tools/compiler/msp430_4.1.5/include" --include_path="/mnt/ccsv5/msp430/include" --include_path="/home/francis/workspace_v5_4/ez430_chronos_datalogger" --include_path="/home/francis/workspace_v5_4/ez430_chronos_datalogger/driver" --include_path="/home/francis/workspace_v5_4/ez430_chronos_datalogger/include" --include_path="/home/francis/workspace_v5_4/ez430_chronos_datalogger/logic" --include_path="/home/francis/workspace_v5_4/ez430_chronos_datalogger/bluerobin" --include_path="/home/francis/workspace_v5_4/ez430_chronos_datalogger/simpliciti" --diag_warning=225 --call_assumptions=0 --auto_inline=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="driver/ports.pp" --obj_directory="driver" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

driver/radio.obj: ../driver/radio.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/mnt/ccsv5/tools/compiler/msp430_4.1.5/bin/cl430" -vmspx -g -O4 --opt_for_speed=0 --define=__CCE__ --define=ISM_LF --include_path="/mnt/ccsv5/ccs_base/msp430/include" --include_path="/mnt/ccsv5/tools/compiler/msp430_4.1.5/include" --include_path="/mnt/ccsv5/msp430/include" --include_path="/home/francis/workspace_v5_4/ez430_chronos_datalogger" --include_path="/home/francis/workspace_v5_4/ez430_chronos_datalogger/driver" --include_path="/home/francis/workspace_v5_4/ez430_chronos_datalogger/include" --include_path="/home/francis/workspace_v5_4/ez430_chronos_datalogger/logic" --include_path="/home/francis/workspace_v5_4/ez430_chronos_datalogger/bluerobin" --include_path="/home/francis/workspace_v5_4/ez430_chronos_datalogger/simpliciti" --diag_warning=225 --call_assumptions=0 --auto_inline=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="driver/radio.pp" --obj_directory="driver" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

driver/rf1a.obj: ../driver/rf1a.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/mnt/ccsv5/tools/compiler/msp430_4.1.5/bin/cl430" -vmspx -g -O4 --opt_for_speed=0 --define=__CCE__ --define=ISM_LF --include_path="/mnt/ccsv5/ccs_base/msp430/include" --include_path="/mnt/ccsv5/tools/compiler/msp430_4.1.5/include" --include_path="/mnt/ccsv5/msp430/include" --include_path="/home/francis/workspace_v5_4/ez430_chronos_datalogger" --include_path="/home/francis/workspace_v5_4/ez430_chronos_datalogger/driver" --include_path="/home/francis/workspace_v5_4/ez430_chronos_datalogger/include" --include_path="/home/francis/workspace_v5_4/ez430_chronos_datalogger/logic" --include_path="/home/francis/workspace_v5_4/ez430_chronos_datalogger/bluerobin" --include_path="/home/francis/workspace_v5_4/ez430_chronos_datalogger/simpliciti" --diag_warning=225 --call_assumptions=0 --auto_inline=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="driver/rf1a.pp" --obj_directory="driver" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


