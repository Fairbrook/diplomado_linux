cmd_/project/Module.symvers := sed 's/ko$$/o/' /project/modules.order | scripts/mod/modpost -m    -o /project/Module.symvers -e -i Module.symvers   -T -
