if {[catch {package require Tcl 8.5}]} return
set script "load \"[file join $dir shellicon22.dll]\" shellicon"
package ifneeded shellicon 2.2.9 $script
