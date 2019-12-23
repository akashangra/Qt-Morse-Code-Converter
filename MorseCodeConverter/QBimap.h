#ifndef QBIMAP_H
#define QBIMAP_H
#include <QHash>
#include <iostream>

template <typename Left,
          typename Right >
/**
 * @brief The QBimap class : used to store two wat mapping in QHash
 * mapping prsent with Key==> Value and Value==>Key both
 */
class QBimap
{
    //hash with left as key and right as value
    QHash<Left,Right> _mapLeftKeyVsRightValue;

    //hash with right as key and left as value
    QHash<Right,Left> _mapRightKeyVsLeftValue;

public:
    QBimap() = default;

    /**
     * @brief insert : used for inserting left and right mapping in bith hashes
     * @param leftVal
     * @param rightVal
     */
    void insert(const Left &leftVal, const Right &rightVal)
    {
        //checking just hash with leftKey because if left is present , right is also present
        if( _mapLeftKeyVsRightValue.find(leftVal) == _mapLeftKeyVsRightValue.end() )
        {
            _mapLeftKeyVsRightValue.insert(leftVal,rightVal);//inserting with left value as key
            _mapRightKeyVsLeftValue.insert(rightVal,leftVal);//inserting with right value as key
        }
        else
        {
            std::cout << " WARNING :: SAME ENTRY REQUESTED" << std::endl;
        }
    }

    /**
     * @brief eraseUsingLeft : used for erasing entries in both hashes using left key
     * @param leftKey
     */
    void eraseUsingLeft( const Left &leftKey )
    {
        auto itrLeft = _mapLeftKeyVsRightValue.find( leftKey );
        if( itrLeft != _mapLeftKeyVsRightValue.end()  )
        {
            //erasing entries in both hashes
            _mapRightKeyVsLeftValue.erase( *itrLeft );
            _mapLeftKeyVsRightValue.erase( itrLeft );
        }
    }

    /**
     * @brief eraseUsingRight : used for erasing entries in both hashes using right key
     * @param rightKey
     */
    void eraseUsingRight( const Right &rightKey )
    {
        auto itrRight = _mapRightKeyVsLeftValue.find( rightKey );
        if( itrRight != _mapRightKeyVsLeftValue.end()  )
        {
            //erasing entries in both hashes
            _mapLeftKeyVsRightValue.erase( *itrRight );
            _mapRightKeyVsLeftValue.erase( itrRight );
        }
    }

    /**
     * @brief getLeftValue : get left value using right key
     * @param rightKey
     * @param leftValue
     * @return : true if key present else false
     */
    bool getLeftValue( const Right &rightKey, Left &leftValue )
    {
        auto itr = _mapRightKeyVsLeftValue.find( rightKey );
        if( itr != _mapRightKeyVsLeftValue.end() )
        {
            leftValue = *itr;
            return true;
        }
        return false;
    }

    /**
     * @brief getRightValue : get right value using left keyS
     * @param leftKey
     * @param rightValue
     * @return : true if key present else false
     */
    bool getRightValue( const Left &leftKey, Right &rightValue)
    {
        auto itr = _mapLeftKeyVsRightValue.find( leftKey );

        if( itr != _mapLeftKeyVsRightValue.end() )
        {
            rightValue = *itr;
            return true;
        }
        return false;
    }

    void clear()
    {
        _mapLeftKeyVsRightValue.clear();
        _mapRightKeyVsLeftValue.clear();
    }

    ~QBimap()
    {
        clear();
    }
};


#endif // QBIMAP_H
