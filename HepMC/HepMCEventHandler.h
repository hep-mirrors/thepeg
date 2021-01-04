
#ifndef THEPEG_HepMCEventHandler_H
#define THEPEG_HepMCEventHandler_H

#include "ThePEG/Handlers/EventHandler.h"
/* #include "HepMCReader.h" */
#include "HepMCEventHandler.fh"
#include "HepMCReader.fh"

namespace ThePEG {

  class HepMCEventHandler: public EventHandler {
    public:

      /**
       *
       * The default constructor
       */
      HepMCEventHandler() {
      }

      /**
       * The destructor
       */
      virtual ~HepMCEventHandler();
    public:

      // With these functins variables of the class are
      // stored to the disk
      //
      /** @name Functions used by the persistent I/O system. */
      //@{
      /**
       * Function used to write out object persistently.
       * @param os the persistent output stream written to.
       */
      void persistentOutput(PersistentOStream & os) const;

      /**
       * Function used to read in object persistently.
       * @param is the persistent input stream read from.
       * @param version the version number of the object when written.
       */
      void persistentInput(PersistentIStream & is, int version);
      //@}

      /**
       * The standard Init function used to initialize the interfaces.
       * Called exactly once for each class by the class description system
       * before the main function starts or
       * when this class is dynamically loaded.
       */
      static void Init();

    public:
      /** @name Initialization and finalization functions. */
      //@{
      /**
       * Initialize this event handler and all related objects needed to
       * generate events.
       */
      virtual void initialize();


      /** @name Functions used for the actual generation */
      //@{
      /**
       * Generate an event.
       */
      virtual EventPtr generateEvent();

      /**
       * Create the Event and Collision objects. Used by the
       * generateEvent() function.
       */
      virtual tCollPtr performCollision();

      /**
       * Continue generating an event if the generation has been stopped
       * before finishing.
       */
      virtual EventPtr continueEvent();
      //@}
      /**
       * Access the list of readers.
       */
      const HepMCReaderPtr & reader() const { return theReader; }

    protected:

      /** @name Clone Methods. */
      //@{
      /**
       * Make a simple clone of this object.
       * @return a pointer to the new object.
       */
      virtual IBPtr clone() const;

      /** Make a clone of this object, possibly modifying the cloned object
       * to make it sane.
       * @return a pointer to the new object.
       */
      virtual IBPtr fullclone() const;
      //@}
    protected:

      /**
       * Initialize this object. Called in the run phase just before
       * a run begins.
       */
      virtual void doinit();

      virtual void doinitrun();

      virtual void dofinish();


    private:
      /**
       * The reader
       */
      HepMCReaderPtr theReader;

    public:

      /** @cond EXCEPTIONCLASSES */
      /**
       * Exception class used if no readers were assigned.
       */
      class HepMCInitError: public InitException {};

      /**
       * Exception class used if error while reading from file
       */
      class HepMCOpenError: public Exception {};
      /** @endcond */

    private:

      /**
       * The static object used to initialize the description of this class.
       * Indicates that this is a concrete class with persistent data.
       */
      static ClassDescription<HepMCEventHandler> initHepMCEventHandler;

      /**
       * The assignment operator is private and must never be called.
       * In fact, it should not even be implemented.
       */
      HepMCEventHandler & operator=(const HepMCEventHandler &) = delete;


  };

  }

  // CLASSDOC OFF
  // TODO: don't know what this is for
  // It's a hook in the interface system of ThePEG

#include "ThePEG/Utilities/ClassTraits.h"

  namespace ThePEG {

    /** @cond TRAITSPECIALIZATIONS */

    /** This template specialization informs ThePEG about the
     *  base classes of HepMCEventHandler. */
    template <>
      struct BaseClassTrait<HepMCEventHandler,1> {
        /** Typedef of the first base class of HepMCEventHandler. */
        typedef EventHandler NthBase;
      };

    /** This template specialization informs ThePEG about the name of
     *  the HepMCEventHandler class and the shared object where it is defined. */
    template <>
      struct ClassTraits<HepMCEventHandler>
      : public ClassTraitsBase<HepMCEventHandler> {
        /** Return a platform-independent class name */
        static string className() { return "ThePEG::HepMCEventHandler"; }
        /** Return the name of the shared library be loaded to get access to
         *  the HepMCEventHandler class and every other class it uses
         *  (except the base class). */
        static string library() { return "HepMCReader.so"; }
      };

    /** @endcond */

  }
#endif /* THEPEG_HepMCEventHandler_H */
