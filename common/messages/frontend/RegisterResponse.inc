<?php
/**
 * Contains response from DB connector when registering a new user.
 *
 * @package JAND\Common\Messages\Frontend\RegisterResponse
 */

namespace JAND\Common\Messages\Frontend;

/**
 * DB connector response to a register request.
 */
class RegisterResponse extends AccountResponse
{

    /**
     * Error when there is a failure.
     *
     * @var ?\JAND\Common\Messages\Shared\OperationError $error Error during registration.
     */
    private ?\JAND\Common\Messages\Shared\OperationError $error;


    /**
     * Create a new register response.
     *
     * @param boolean                                     $result  True on success, otherwise false.
     * @param \JAND\Common\Session                        $session The session object on success.
     * @param \JAND\Common\Messages\Shared\OperationError $error   Error when registration is rejected.
     * */
    public function __construct(
        bool $result,
        ?\JAND\Common\Session $session,
        ?\JAND\Common\Messages\Shared\OperationError $error=null
    ) {
        parent::__construct($result, $session);
        $this->error = $error;

    }//end __construct()


    /**
     * Gets registration error.
     *
     * @return ?RegistrationError Registration error.
     */
    public function getError()
    {
        return $this->error;

    }//end getError()


}//end class
