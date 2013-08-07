
(cl:in-package :asdf)

(defsystem "ardros-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "SetDriveControlGains" :depends-on ("_package_SetDriveControlGains"))
    (:file "_package_SetDriveControlGains" :depends-on ("_package"))
  ))