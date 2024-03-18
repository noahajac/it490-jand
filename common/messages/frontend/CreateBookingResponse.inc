<?php
/**
 * Response when creating a booking.
 *
 * @package JAND\Common\Messages\Frontend\CreateBookingResponse
 */

namespace JAND\Common\Messages\Frontend;

/**
 * Response when deleting a booking.
 */
class CreateBookingResponse
{

    /**
     * Error, if there is one. Null on success.
     *
     * @var ?\JAND\Common\Messages\Shared\OperationError $error Error or null.
     */
    private ?\JAND\Common\Messages\Shared\OperationError $error;


    /**
     * Creates a response for creating a booking.
     *
     * @param \JAND\Common\Messages\Shared\OperationError $error Error, if there is one.
     */
    public function __construct(?\JAND\Common\Messages\Shared\OperationError $error=null)
    {
        $this->error = $error;

    }//end __construct()


    /**
     * Gets error.
     *
     * @return ?\JAND\Common\Messages\Shared\OperationError Null on success.
     */
    public function getError()
    {
        return $this->error;

    }//end getError()


}//end class
