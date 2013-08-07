; Auto-generated. Do not edit!


(cl:in-package playground-srv)


;//! \htmlinclude SetDriveControlGains-request.msg.html

(cl:defclass <SetDriveControlGains-request> (roslisp-msg-protocol:ros-message)
  ((kp
    :reader kp
    :initarg :kp
    :type cl:float
    :initform 0.0)
   (ki
    :reader ki
    :initarg :ki
    :type cl:float
    :initform 0.0)
   (kd
    :reader kd
    :initarg :kd
    :type cl:float
    :initform 0.0))
)

(cl:defclass SetDriveControlGains-request (<SetDriveControlGains-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetDriveControlGains-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetDriveControlGains-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name playground-srv:<SetDriveControlGains-request> is deprecated: use playground-srv:SetDriveControlGains-request instead.")))

(cl:ensure-generic-function 'kp-val :lambda-list '(m))
(cl:defmethod kp-val ((m <SetDriveControlGains-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader playground-srv:kp-val is deprecated.  Use playground-srv:kp instead.")
  (kp m))

(cl:ensure-generic-function 'ki-val :lambda-list '(m))
(cl:defmethod ki-val ((m <SetDriveControlGains-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader playground-srv:ki-val is deprecated.  Use playground-srv:ki instead.")
  (ki m))

(cl:ensure-generic-function 'kd-val :lambda-list '(m))
(cl:defmethod kd-val ((m <SetDriveControlGains-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader playground-srv:kd-val is deprecated.  Use playground-srv:kd instead.")
  (kd m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetDriveControlGains-request>) ostream)
  "Serializes a message object of type '<SetDriveControlGains-request>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'kp))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'ki))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'kd))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetDriveControlGains-request>) istream)
  "Deserializes a message object of type '<SetDriveControlGains-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'kp) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ki) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'kd) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetDriveControlGains-request>)))
  "Returns string type for a service object of type '<SetDriveControlGains-request>"
  "playground/SetDriveControlGainsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetDriveControlGains-request)))
  "Returns string type for a service object of type 'SetDriveControlGains-request"
  "playground/SetDriveControlGainsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetDriveControlGains-request>)))
  "Returns md5sum for a message object of type '<SetDriveControlGains-request>"
  "08d0ca1f582560895ecba909de1d88ec")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetDriveControlGains-request)))
  "Returns md5sum for a message object of type 'SetDriveControlGains-request"
  "08d0ca1f582560895ecba909de1d88ec")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetDriveControlGains-request>)))
  "Returns full string definition for message of type '<SetDriveControlGains-request>"
  (cl:format cl:nil "float32 kp~%float32 ki~%float32 kd~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetDriveControlGains-request)))
  "Returns full string definition for message of type 'SetDriveControlGains-request"
  (cl:format cl:nil "float32 kp~%float32 ki~%float32 kd~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetDriveControlGains-request>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetDriveControlGains-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetDriveControlGains-request
    (cl:cons ':kp (kp msg))
    (cl:cons ':ki (ki msg))
    (cl:cons ':kd (kd msg))
))
;//! \htmlinclude SetDriveControlGains-response.msg.html

(cl:defclass <SetDriveControlGains-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass SetDriveControlGains-response (<SetDriveControlGains-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetDriveControlGains-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetDriveControlGains-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name playground-srv:<SetDriveControlGains-response> is deprecated: use playground-srv:SetDriveControlGains-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetDriveControlGains-response>) ostream)
  "Serializes a message object of type '<SetDriveControlGains-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetDriveControlGains-response>) istream)
  "Deserializes a message object of type '<SetDriveControlGains-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetDriveControlGains-response>)))
  "Returns string type for a service object of type '<SetDriveControlGains-response>"
  "playground/SetDriveControlGainsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetDriveControlGains-response)))
  "Returns string type for a service object of type 'SetDriveControlGains-response"
  "playground/SetDriveControlGainsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetDriveControlGains-response>)))
  "Returns md5sum for a message object of type '<SetDriveControlGains-response>"
  "08d0ca1f582560895ecba909de1d88ec")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetDriveControlGains-response)))
  "Returns md5sum for a message object of type 'SetDriveControlGains-response"
  "08d0ca1f582560895ecba909de1d88ec")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetDriveControlGains-response>)))
  "Returns full string definition for message of type '<SetDriveControlGains-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetDriveControlGains-response)))
  "Returns full string definition for message of type 'SetDriveControlGains-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetDriveControlGains-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetDriveControlGains-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetDriveControlGains-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetDriveControlGains)))
  'SetDriveControlGains-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetDriveControlGains)))
  'SetDriveControlGains-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetDriveControlGains)))
  "Returns string type for a service object of type '<SetDriveControlGains>"
  "playground/SetDriveControlGains")