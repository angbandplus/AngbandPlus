;;; -*- Mode: Lisp; Syntax: Common-Lisp; Package: org.langband.engine -*-

#|

DESC: parameters.lisp - handling of special parameters
Copyright (c) 2000-2002 - Stig Erik Sand�

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

|#

(in-package :org.langband.engine)


(defclass game-parameter ()
  ((key :accessor param.key
	:initarg :key :initform nil)
   (name :accessor param.name
	 :initarg :name :initform nil)
   (desc :accessor param.desc
	 :initarg :desc :initform nil)
   (value :accessor param.value
	  :initarg :value :initform nil)
   (alternatives :accessor param.alts
		 :initarg :alternatives
		 :initform nil)))

(defclass param-alt ()
  ((key  :accessor param-alt.key :initarg :key :initform nil)
   (name :accessor param-alt.name :initarg :name :initform nil)
   (desc :accessor param-alt.desc :initarg :desc :initform nil)))


(defun make-game-parameter (key name desc value alts)
  "Please look at DEFINE-PARAMETER."
  (make-instance 'game-parameter :key key :name name :desc desc :value value
		 :alternatives alts))

(defun make-parameter-alternative (key name desc)
  "Creates a parameter alternative and returns it."
  (make-instance 'param-alt :key key :name name :desc desc))

(defun game-parameter (key)
  "Returns the parameter identified by key."
  (gethash key *game-parameters*))

(defun (setf game-parameter) (param key)
  (unless (eq key (param.key param))
    (warn "Key ~a and param.key ~a doesn't match" key (param.key param)))
  (setf (gethash key *game-parameters*) param))

(defun game-parameter-value (key)
  "Returns the value for the parameter identified by key or NIL."
  (let ((param (game-parameter key)))
    (if param
	(param.value param)
	nil)))

(defun customise-game-parameters& (param-list)
  "The param-list should be a list of the form:
'((param-key-1 . value) (param-key-2 .value) ...)"

  (dolist (i param-list)
    (let ((found-param (game-parameter (car i))))
      (if found-param
	  (if (legal-param-value? (cdr i) (param.alts found-param))
	      (setf (param.value found-param) (cdr i))
	      (warn "The requested value ~a for parameter ~a is not found in alternative list."
		    (cdr i) (car i)))
	  (warn "Unable to find a parameter with key ~a" (car i)))))

  (values))


(defun legal-param-value? (param-key alts)
  "Checks if the param-key-value is allowed from the given alternative list"
  (dolist (i alts)
    (when (eq param-key (param-alt.key i))
      (return-from legal-param-value? t)))
  
  ;; default is of course nil
  nil)

(defun define-parameter (key name desc init-val alternatives)
  "defines a parameter for later use in the game"
  (let ((retval nil))
    (if (legal-param-value? init-val alternatives)
	(let ((param-obj (make-game-parameter key name desc init-val alternatives))
	      (existing-param (game-parameter key)))
	  (when (and existing-param (not (equal (param.name existing-param) (param.name param-obj))))
	    (warn "Replacing old parameter ~a with ~a.~a"
		  (param.name existing-param) (param.name param-obj)
		  (if (string-equal (param.name existing-param) (param.name param-obj))
		      " [Probably ok.]"
		      "")))
	  (setf (game-parameter key) param-obj)
	  (setf retval param-obj))
	
	;; if not legal value
	(warn "The init-value is not found in the alternative list"))

    retval))

				    
;;; Some parameter definitions.. move them later:


;; langband default parameters
    
(define-parameter :initial-backpack
    "Initial backpack"
  "This value sets which backpack which is default for starting
characters"
  :backpack  ;; default value
  (list (make-parameter-alternative :backpack
				    "A normal backpack"
				    "This is the vanilla backpack with room for 23 objects.")
	(make-parameter-alternative :small-backpack
				    "A small backpack"
				    "This is a smaller backpack with only room for 10 objects.")))

(define-parameter :backpack-constant-p
    "Can the backpack be changed?"
  "This value sets whether the character can choose appropriate
backpack himself  or if it is set in stone, ie vanilla."
  :yes  ;; default value
  (list (make-parameter-alternative :yes
				    "Backpack is constant"
				    "You cannot change backpack, just like in vanilla.")
	(make-parameter-alternative :no
				    "Backpack is not constant"
				    "You can buy and change backpack like other equipment.")))

(define-parameter :equipment-organisation
    "How are equipment slots organised?"
  "With this parameter you can change how equipment is handled.
Currently only available in vanilla mode."
  :vanilla  ;; default value
  (list (make-parameter-alternative :vanilla
				    "Vanilla equipment org."
				    "weapon, bow, armour, shield, light and cloak slots.")))

