/* 
the detail method of insert.(simplified version)

when position != end()

if(finish != end_of_storage)
{
    construct( finish,*(finish - 1) ); // establishing a new memory unit in finish and assign the content of (finish - 1) to that place. 
    copy_backward(position,finish-1,finish);
    ++finish;
}

//if finish == end_of_storage
iterator insert(iterator position,const T & x)
{
    //...
    size_type len = size()? 2*size() : static_allocator.init_page_size();
    iterator tmp = static_allocator.allocate(len);
    uninitialized_copy( begin(), position , tmp);
    construct( tmp + position - begin(),x )
    uninitialized_copy( position,end(), tmp + position -begin() + 1 );
    destroy( begin(), end() );
    static.allocator.deallocate( begin() );
    end_of_storage = tmp + len;
    finish = tmp + size() + 1;
    start = tmp;
}

*/
