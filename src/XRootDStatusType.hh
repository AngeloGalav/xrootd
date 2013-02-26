//------------------------------------------------------------------------------
// Copyright (c) 2012-2013 by European Organization for Nuclear Research (CERN)
// Author: Justin Salmon <jsalmon@cern.ch>
//------------------------------------------------------------------------------
// XRootD is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// XRootD is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with XRootD.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#ifndef XROOTDSTATUSTYPE_HH_
#define XROOTDSTATUSTYPE_HH_

#include <Python.h>
#include "structmember.h"

#include "XrdCl/XrdClXRootDResponses.hh"

namespace XrdClBind
{
  //----------------------------------------------------------------------------
  //! XRootDStatus binding type definition
  //----------------------------------------------------------------------------
  typedef struct
  {
      PyObject_HEAD
      /* Type-specific fields */
      XrdCl::XRootDStatus *status;
  } XRootDStatus;

  //----------------------------------------------------------------------------
  //! Deallocation function, called when object is deleted
  //----------------------------------------------------------------------------
  static void XRootDStatus_dealloc( XRootDStatus *self )
  {
    delete self->status;
    self->ob_type->tp_free( (PyObject*) self );
  }

  //----------------------------------------------------------------------------
  //! __init__() equivalent
  //----------------------------------------------------------------------------
  static int XRootDStatus_init( XRootDStatus *self, PyObject *args,
      PyObject *kwds )
  {
    static char *kwlist[] = { "status", "code", "errNo", "message", NULL };

    uint16_t status, code;
    uint32_t errNo;
    const char *message;

    if ( !PyArg_ParseTupleAndKeywords( args, kwds, "HHIs", kwlist, &status,
                                       &code, &errNo, &message ) )
      return -1;

    self->status = new XrdCl::XRootDStatus( status, code, errNo,
                                            std::string( message ) );

    return 0;
  }

  //----------------------------------------------------------------------------
  //! __str__() equivalent
  //----------------------------------------------------------------------------
  static PyObject* XRootDStatus_str( XRootDStatus *status )
  {
    return PyString_FromString( status->status->ToStr().c_str() );
  }

  //----------------------------------------------------------------------------
  //! Getter for XRootDStatus.status
  //----------------------------------------------------------------------------
  static PyObject* XRootDStatus_GetStatus( XRootDStatus *self, void *closure )
  {
    return Py_BuildValue( "i", self->status->status );
  }

  //----------------------------------------------------------------------------
  //! Getter for XRootDStatus.code
  //----------------------------------------------------------------------------
  static PyObject* XRootDStatus_GetCode( XRootDStatus *self, void *closure )
  {
    return Py_BuildValue( "i", self->status->code );
  }

  //----------------------------------------------------------------------------
  //! Getter for XRootDStatus.errNo
  //----------------------------------------------------------------------------
  static PyObject* XRootDStatus_GetErrNo( XRootDStatus *self, void *closure )
  {
    return Py_BuildValue( "i", self->status->errNo );
  }

  //----------------------------------------------------------------------------
  //! Get error message
  //----------------------------------------------------------------------------
  static PyObject* GetErrorMessage( XRootDStatus *self )
  {
    return Py_BuildValue( "s", self->status->GetErrorMessage().c_str() );
  }

  //----------------------------------------------------------------------------
  //! Getter for XRootDStatus.errNo
  //----------------------------------------------------------------------------
  static PyObject* GetShellCode( XRootDStatus *self )
  {
    return Py_BuildValue( "i", self->status->GetShellCode() );
  }

  //----------------------------------------------------------------------------
  //! Error
  //----------------------------------------------------------------------------
  static PyObject* IsError( XRootDStatus *self )
  {
    return Py_BuildValue( "O", PyBool_FromLong( self->status->IsError() ) );
  }

  //----------------------------------------------------------------------------
  //! Fatal error
  //----------------------------------------------------------------------------
  static PyObject* IsFatal( XRootDStatus *self )
  {
    return Py_BuildValue( "O", PyBool_FromLong( self->status->IsFatal() ) );
  }

  //----------------------------------------------------------------------------
  //! We're fine
  //----------------------------------------------------------------------------
  static PyObject* IsOK( XRootDStatus *self )
  {
    return Py_BuildValue( "O", PyBool_FromLong( self->status->IsOK() ) );
  }

  //----------------------------------------------------------------------------
  //! Custom getter/setter function declarations
  //----------------------------------------------------------------------------
  static PyGetSetDef XRootDStatusGetSet[] =
    {
      { "status", (getter) XRootDStatus_GetStatus, NULL,
        "Status of the execution", NULL },
      { "code", (getter) XRootDStatus_GetCode, NULL,
        "Error type, or additional hints on what to do", NULL },
      { "errNo", (getter) XRootDStatus_GetErrNo, NULL,
        "Errno, if any", NULL },
      { NULL } /* Sentinel */
    };

  //----------------------------------------------------------------------------
  //! Visible member definitions
  //----------------------------------------------------------------------------
  static PyMemberDef XRootDStatusMembers[] =
    {
      { NULL } /* Sentinel */
    };

  //----------------------------------------------------------------------------
  //! Visible method definitions
  //----------------------------------------------------------------------------
  static PyMethodDef XRootDStatusMethods[] =
    {
      { "IsError", (PyCFunction) IsError, METH_NOARGS,
          "Return whether this status has an error" },
      { "IsFatal", (PyCFunction) IsFatal, METH_NOARGS,
          "Return whether this status has a fatal error" },
      { "IsOK", (PyCFunction) IsOK, METH_NOARGS,
          "Return whether this status completed successfully" },
      { "GetErrorMessage", (PyCFunction) GetErrorMessage, METH_NOARGS,
          "Return the error message" },
      { "GetShellCode", (PyCFunction) GetShellCode, METH_NOARGS,
          "Return the status code that may be returned to the shell" },
      { NULL } /* Sentinel */
    };

  //----------------------------------------------------------------------------
  //! XRootDStatus binding type object
  //----------------------------------------------------------------------------
  static PyTypeObject XRootDStatusType = {
    PyObject_HEAD_INIT(NULL)
    0,                                          /* ob_size */
    "client.XRootDStatus",                      /* tp_name */
    sizeof(XRootDStatus),                       /* tp_basicsize */
    0,                                          /* tp_itemsize */
    (destructor) XRootDStatus_dealloc,          /* tp_dealloc */
    0,                                          /* tp_print */
    0,                                          /* tp_getattr */
    0,                                          /* tp_setattr */
    0,                                          /* tp_compare */
    0,                                          /* tp_repr */
    0,                                          /* tp_as_number */
    0,                                          /* tp_as_sequence */
    0,                                          /* tp_as_mapping */
    0,                                          /* tp_hash */
    0,                                          /* tp_call */
    (reprfunc) XRootDStatus_str,                /* tp_str */
    0,                                          /* tp_getattro */
    0,                                          /* tp_setattro */
    0,                                          /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,   /* tp_flags */
    "XRootDStatus object",                      /* tp_doc */
    0,                                          /* tp_traverse */
    0,                                          /* tp_clear */
    0,                                          /* tp_richcompare */
    0,                                          /* tp_weaklistoffset */
    0,                                          /* tp_iter */
    0,                                          /* tp_iternext */
    XRootDStatusMethods,                        /* tp_methods */
    XRootDStatusMembers,                        /* tp_members */
    XRootDStatusGetSet,                         /* tp_getset */
    0,                                          /* tp_base */
    0,                                          /* tp_dict */
    0,                                          /* tp_descr_get */
    0,                                          /* tp_descr_set */
    0,                                          /* tp_dictoffset */
    (initproc) XRootDStatus_init,               /* tp_init */
  };
}

#endif /* XROOTDSTATUSTYPE_HH_ */
