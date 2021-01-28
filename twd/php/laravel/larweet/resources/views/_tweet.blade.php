   <div class="flex p-4 border-b border-b-gray-400">

       <!-- AVATAR -->
       <div class="mr-2 flex-shrink-0">
           <img src="{{ $tweet->user->getAvatar(50) }}" 
               alt="avatar"
               class="rounded-full mr-2"
           >
       </div>

       <!-- POST -->
       <div>
           <a href="/users/{{ $tweet->user->name }}">
                <h5 class="font-bold mb-4">{{ $tweet->user->name }}</h5>
           </a>
           <p class="text-sm text-black">
               {{ $tweet->body }}
           </p>
       </div>
   </div>