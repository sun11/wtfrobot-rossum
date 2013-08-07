; Auto-generated. Do not edit!


(cl:in-package ardros-srv)


;//! \htmlinclude SetDriveControlGains-request.msg.html

(cl:defclass <SetDriveControlGains-request> (roslisp-msg-protocol:ros-message)
  ((velocityPParam
    :reader velocityPParam
    :initarg :velocityPParam
    :type cl:float
    :initform 0.0)
   (velocityIParam
    :reader velocityIParam
    :initarg :velocityIParam
    :type cl:float
    :initform 0.0)
   (turnPParam
    :reader turnPParam
    :initarg :turnPParam
    :type cl:float
    :initform 0.0)
   (turnIParam
    :reader turnIParam
    :initarg :turnIParam
    :type cl:float
    :initform 0.0))
)

(cl:defclass SetDriveControlGains-request (<SetDriveControlGains-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetDriveControlGains-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetDriveControlGains-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ardros-srv:<SetDriveControlGains-request> is deprecated: use ardros-srv:SetDriveControlGains-request instead.")))

(cl:ensure-generic-function 'velocityPParam-val :lambda-list '(m))
(cl:defmethod velocityPParam-val ((m <SetDriveControlGains-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ardros-srv:velocityPParam-val is deprecated.  Use ardros-srv:velocityPParam instead.")
  (velocityPParam m))

(cl:ensure-generic-function 'velocityIParam-val :lambda-list '(m))
(cl:defmethod velocityIParam-val ((m <SetDriveControlGains-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ardros-srv:velocityIParam-val is deprecated.  Use ardros-srv:velocityIParam instead.")
  (velocityIParam m))

(cl:ensure-generic-function 'turnPParam-val :lambda-list '(m))
(cl:defmethod turnPParam-val ((m <SetDriveControlGains-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ardros-srv:turnPParam-val is deprecated.  Use ardros-srv:turnPParam instead.")
  (turnPParam m))

(cl:ensure-generic-function 'turnIParam-val :lambda-list '(m))
(cl:defmethod turnIParam-val ((m <SetDriveControlGains-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ardros-srv:turnIParam-val is deprecated.  Use ardros-srv:turnIParam instead.")
  (turnIParam m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetDriveControlGains-request>) ostream)
  "Serializes a message object of type '<SetDriveControlGains-request>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'velocityPParam))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'velocityIParam))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'turnPParam))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'turnIParam))))
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
    (cl:setf (cl:slot-value msg 'velocityPParam) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'velocityIParam) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'turnPParam) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'turnIParam) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetDriveControlGains-request>)))
  "Returns string type for a service object of type '<SetDriveControlGains-request>"
  "ardros/SetDriveControlGainsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetDriveControlGains-request)))
  "Returns string type for a service object of type 'SetDriveControlGains-request"
  "ardros/SetDriveControlGainsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetDriveControlGains-request>)))
  "Returns md5sum for a message object of type '<SetDriveControlGains-request>"
  "7ef02095d661072b02e76d2e1f6bddf8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetDriveControlGains-request)))
  "Returns md5sum for a message object of type 'SetDriveControlGains-request"
  "7ef02095d661072b02e76d2e1f6bddf8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetDriveControlGains-request>)))
  "Returns full string definition for message of type '<SetDriveControlGains-request>"
  (cl:format cl:nil "float32 velocityPParam~%float32 velocityIParam~%float32 turnPParam~%float32 turnIParam~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetDriveControlGains-request)))
  "Returns full string definition for message of type 'SetDriveControlGains-request"
  (cl:format cl:nil "float32 velocityPParam~%float32 velocityIParam~%float32 turnPParam~%float32 turnIParam~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetDriveControlGains-request>))
  (cl:+ 0
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetDriveControlGains-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetDriveControlGains-request
    (cl:cons ':velocityPParam (velocityPParam msg))
    (cl:cons ':velocityIParam (velocityIParam msg))
    (cl:cons ':turnPParam (turnPParam msg))
    (cl:cons ':turnIParam (turnIParam msg))
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
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ardros-srv:<SetDriveControlGains-response> is deprecated: use ardros-srv:SetDriveControlGains-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetDriveControlGains-response>) ostream)
  "Serializes a message object of type '<SetDriveControlGains-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetDriveControlGains-response>) istream)
  "Deserializes a message object of type '<SetDriveControlGains-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetDriveControlGains-response>)))
  "Returns string type for a service object of type '<SetDriveControlGains-response>"
  "ardros/SetDriveControlGainsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetDriveControlGains-response)))
  "Returns string type for a service object of type 'SetDriveControlGains-response"
  "ardros/SetDriveControlGainsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetDriveControlGains-response>)))
  "Returns md5sum for a message object of type '<SetDriveControlGains-response>"
  "7ef02095d661072b02e76d2e1f6bddf8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetDriveControlGains-response)))
  "Returns md5sum for a message object of type 'SetDriveControlGains-response"
  "7ef02095d661072b02e76d2e1f6bddf8")
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
  "ardros/SetDriveControlGains")