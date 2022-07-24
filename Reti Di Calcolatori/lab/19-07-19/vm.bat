:: Macchina X con ip 4::AA:BBC
VBoxManage clonevm test --snapshot Snapshot --name X --options link --register
VBoxManage modifyvm X --nic1 intnet --intnet1 lanISP --nic2 none --nic3 none --nic4 none

:: Router ISP 
VBoxManage clonevm test --snapshot Snapshot --name ISP --options link --register
VBoxManage modifyvm ISP --nic1 intnet --intnet1 lanISP --nic2 intnet --intnet2 lan00 --nic3 none --nic4 none

:: Router R0
VBoxManage clonevm test --snapshot Snapshot --name R0 --options link --register
VBoxManage modifyvm R0 --nic1 intnet --intnet1 lan00 --nic2 intnet --intnet2 lan01 --nic3 none --nic4 none

:: Router R1
VBoxManage clonevm test --snapshot Snapshot --name R1 --options link --register
VBoxManage modifyvm R1 --nic1 intnet --intnet1 lan01 --nic2 intnet --intnet2 lan06 --nic3 intnet --intnet3 lan04 --nic4 intnet --intnet4 lan05

:: Router R2
VBoxManage clonevm test --snapshot Snapshot --name R2 --options link --register
VBoxManage modifyvm R2 --nic1 intnet --intnet1 lan06 --nic2 intnet --intnet2 lan02 --nic3 intnet --intnet3 lan03 --nic4 none

:: Macchina A nella lan01
VBoxManage clonevm test --snapshot Snapshot --name A --options link --register
VBoxManage modifyvm A --nic1 intnet --intnet1 lan01 --nic2 none --nic3 none --nic4 none

:: Macchina B nella lan06
VBoxManage clonevm test --snapshot Snapshot --name B --options link --register
VBoxManage modifyvm B --nic1 intnet --intnet1 lan06 --nic2 none --nic3 none --nic4 none

:: Macchina C nella lan02
VBoxManage clonevm test --snapshot Snapshot --name C --options link --register
VBoxManage modifyvm C --nic1 intnet --intnet1 lan02 --nic2 none --nic3 none --nic4 none

:: Macchina D nella lan03
VBoxManage clonevm test --snapshot Snapshot --name D --options link --register
VBoxManage modifyvm D --nic1 intnet --intnet1 lan03 --nic2 none --nic3 none --nic4 none

:: Macchina E nella lan03
VBoxManage clonevm test --snapshot Snapshot --name E --options link --register
VBoxManage modifyvm E --nic1 intnet --intnet1 lan03 --nic2 none --nic3 none --nic4 none

:: Macchina F nella lan04
VBoxManage clonevm test --snapshot Snapshot --name F --options link --register
VBoxManage modifyvm F --nic1 intnet --intnet1 lan04 --nic2 none --nic3 none --nic4 none

:: Macchina G nella lan04
VBoxManage clonevm test --snapshot Snapshot --name G --options link --register
VBoxManage modifyvm G --nic1 intnet --intnet1 lan04 --nic2 none --nic3 none --nic4 none

:: Macchina H nella lan05
VBoxManage clonevm test --snapshot Snapshot --name H --options link --register
VBoxManage modifyvm H --nic1 intnet --intnet1 lan05 --nic2 none --nic3 none --nic4 none

:: Macchina J nella lan05
VBoxManage clonevm test --snapshot Snapshot --name J --options link --register
VBoxManage modifyvm J --nic1 intnet --intnet1 lan05 --nic2 none --nic3 none --nic4 none




